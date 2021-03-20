### CS144 lab0

- - -

#### 一、 Writing webget
**实验说明**
实现`webget`：在互联网中，使用操作系统的 TCP 模块和 socket 来实现一个获取Web网页的程序，就像前面的实验那样。

1. 打开apps/webget.cc文件在文本编辑器或 IDE 中

2. 在 get_URL 函数中，找到注释`// Your code here`

3. 根据文件中的描述，使用http请求实现一个简单的Web客户端。使用`TCPSocket`和`Address`类

4.	提示：
	- 请注意，在http中，每一行必须以 `"\r\n"`结尾（而不是以`“\n”`或`endl`）
	- 当你写完对socket请求，告诉服务器你已经完成request通过结束向外输出的字节流（此字节流从你的socket模块到服务器的socket模块）。你可以通过使用参数`SHUT_WR`调用`TCPSocket`的方法`shutdown`。在 response 中，服务器将会发送给你一个回复，然后会结束它的向外输出流（从服务器 socket 到你的 socket ）。你将会发现传入的输出流已经结束，因为当你读取全部的从服务传来字节流，socket 将会达到`“EOF”`（end of file）。（如果你没有关闭你的向外的输出流，服务器将不会结束它向外的输出流，而是会再等一段时间，等待你发送其他的请求）
	- 当服务器收到`EOF`，确认读取并输出全部的从服务器传来的字节，仅仅调用raad是不够的
	- 我们预计您需要编写大约10行代码
	
5. 运行`make`编译你的程序。如果你看到错误提示，你需要修改你的程序。

6. 通过在build目录运行`./apps/webget cs144.keithw.org /hello`测试你的程序。对比这个结果与你直接在浏览器中访问` http://cs144.keithw.org/hello`有什么不同。相比section 2.1 有什么不同？你可以测试你喜欢的任何 http URL。

7. 当程序看起来运行正常的时候，运行`make check_webget`去运行自动测试。在没有实现函数get_URL之前，你可能会看到以下信息：
   	1/1 Test #25: lab0_webget ......................***Failed    0.00 secFunction called: get_URL(cs144.keithw.org, /hasher/xyzzy).Warning: get_URL() has not been implemented yet.ERROR: webget returned output that did not match the test's expectations

   在实现函数之后，你将会看到：

   4/4 Test #4: lab0_webget ......................   Passed    0.14 sec100% tests passed, 0 tests failed out of 4

8.  评测程序将会使用一个不同的hostname和path运行你的webget程序，而不是使用make check。因此，确保它不仅仅能运行在与make check使用的主机名和路径

**实验代码**
```cpp
void get_URL(const string &host, const string &path) {
    TCPSocket socket;
    socket.connect(Address(host, "http"));
    string write_buffer= "GET "+ path + " HTTP/1.1\r\n" + "Host: "+host+"\r\n\r\n";
    socket.write(write_buffer);
    while(!socket.eof()) {
        string read_buffer = socket.read();
        cout << read_buffer;  //此处不要添加cout
    }
}
```

***

#### An in-memory reliable byte stream

打目前为止，你已经看到TCP抽象模型在Internet实现可靠的字节有序的字节流，即使互联网本身仅提供 “尽最大努力交付” 数据报的服务。

要完成这个 lab， 你需要在单独的电脑上实现这个抽象模型。字节流可以写入缓冲区，也可以被以相同的序列从缓冲区读出来。字节流的长度是有限的：writer 可以结束输入，然后不再向缓冲区中写入字节。当 reader 读取到字节流的末尾，将会到达`EOF `的位置，不再有字节可以读取。

字节流也需要流控制：以特定容量值初始化缓冲区，缓冲区的字符将会被保存在内存中。缓冲区代表着节流。缓冲区将会限制writer当前能够写入的最大长度，以确保字节流的长度不会超过缓冲区的容量。当reader读取字节并将字节从缓冲区中取出，writer 才会被允许写入更多的字节。

你的直接录实现需要使用单线程，因此你不必担心并发读写、锁、条件变量竞争。

下面是一些 writer 的接口：

```cpp
// Write a string of bytes into the stream. Write as many
// as will fit, and return the number of bytes written.
size_t write(const std::string &data);
// Returns the number of additional bytes that the stream has space for
size_t remaining_capacity() const;
// Signal that the byte stream has reached its ending
void end_input();
// Indicate that the stream suffered an error
void set_error();
```

下面是 一些 reader 的接口

```cpp
// Peek at next "len" bytes of the stream
std::string peek_output(const size_t len) const;
// Remove ``len'' bytes from the buffer
void pop_output(const size_t len);
// Read (i.e., copy and then pop) the next "len" bytes of the stream
std::string read(const size_t len);
// `true` if the stream input has ended
bool input_ended() const;
// `true` if the output has reached the ending
bool eof() const;
// `true` if the stream has suffered an error
bool error() const;
// the maximum amount that can currently be peeked/read
size_t buffer_size() const;
// `true` if the buffer is empty
bool buffer_empty() const;
```
打开文件 `libsponge/bytestream.hh`和`libsponge/bytestream.cc`, 并且实现上面提供的函数接口的函数实体。当你完成后，运行`make check_lab0`进行检查。

**实现代码**

在ByteStream定义中添加属性
```cpp
class ByteStream {
  private:
    std::string _buffer;
    size_t _capacity{0};
    size_t _cur_size{0};
    bool _end_input{false};
    size_t _bytes_has_written{0};
    size_t _bytes_has_read{0};

    bool _error{};  
public:
	...
}
```
接口实现代码
```cpp
ByteStream::ByteStream(const size_t capacity) 
: _buffer{}, _capacity(capacity)
{ }

size_t ByteStream::write(const string &data)
{
    if(_end_input) return 0;
    size_t data_size = data.size();
    if(_cur_size+data_size<=_capacity) {
        _buffer += data;
        _cur_size += data_size;
        _bytes_has_written += data_size;
        return data_size;
    }  else {
        size_t can_write_size = _capacity-_cur_size;
        _buffer += data.substr(0, can_write_size);
        _cur_size = _capacity;
        _bytes_has_written += can_write_size;
        return can_write_size;
    } 
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    if(len >= _cur_size) {
        return _buffer;
    } else {
        return _buffer.substr(0, len);
    }
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {  
    if(len <= _cur_size) {
        _bytes_has_read += len;
        _buffer = _buffer.substr(len);
        _cur_size -= len;
    } else {
        _bytes_has_read += _cur_size;
        _buffer.clear();
        _cur_size = 0;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string result;
    if(len <= _cur_size) {
        _bytes_has_read += len;
        result =  _buffer.substr(0, len);
        _buffer = _buffer.substr(len);
        _cur_size -= len;
    } else {
        result =_buffer;
        _buffer.clear();
        _bytes_has_read += _cur_size;
        _cur_size = 0;
    }
    return result;
}

void ByteStream::end_input() { _end_input = true; }

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _cur_size; }

bool ByteStream::buffer_empty() const { return _cur_size == 0; }

bool ByteStream::eof() const { return _cur_size == 0 && _end_input; } // 需要结束输入和当前缓存区为空， 同时满足

size_t ByteStream::bytes_written() const { return _bytes_has_written; }

size_t ByteStream::bytes_read() const { return _bytes_has_read; }

size_t ByteStream::remaining_capacity() const { return _capacity - _cur_size; }
```