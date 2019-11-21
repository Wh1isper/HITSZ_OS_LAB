环境：

python3
	
> gcore <pid\>
> 

生成core.pid文件

> 
> python qq\_mem.py <core_file\> -n


-l 为实验性功能 显示长文本

原理：

聊天记录为utf-8编码，字符串带有前缀

LEN+4 0a LEN+2 0a LEN

利用正则匹配，然后解码即可

注：windows下为Unicode编码，一样可以使用