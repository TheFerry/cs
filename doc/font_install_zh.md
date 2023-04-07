[toc]

## 字体安装
这个项目使用了[nerd font](https://www.nerdfonts.com/)，请确保终端使用的字体是任意一种[nerd font](https://www.nerdfonts.com/)。

如果没有安装nerd font，请前往[这里](https://www.nerdfonts.com/)下载并安装字体。
### linux系统
> 如果您使用的是linux系统:
>
> 您可以使用以下命令查看已经安装的字体:

```sh
fc-list | less
```

> 如果有nerdfont，请将终端的字体设置为任意一种nerdfont。
>
> 如果没有，在上面提供的地址中下载好您喜欢的nerdfont之后，先将字体文件解压出来，这里以我下载的`Agave Nerd Font`为例,下载好后的文件是`Agave.zip`。

> 首先，我们要创建一个目录存储我们的字体,这里以创建一个AgaveNerd目录为例。

```sh
mkdir AgaveNerd
```
> 然后将刚刚下载好的字体文件移动到创建好的目录中。然后进入到目录中
```sh
mv Agave.zip AgaveNerd &&cd AgaveNerd
```
> 解压`zip`格式的压缩包需要使用`unzip`命令,如果您没有`unzip`命令，请先下载`unzip`命令。如果有的话请先跳过该段。


> 如果您的linux是基于Debian的系统，您可以使用下面的命令安装:
```sh
sudo apt install unzip
```
> 如果您的系统是基于Red Hat的，您可以使用以下命令安装:
```sh
sudo yum install unzip
```
> 如果您的系统是Arch系的，您可以使用下面命令安装:
```sh
sudo pacman -S unzip
```
> 对于其他linux发行版您可以去unzip的[官网](https://infozip.sourceforge.net/)自行下载安装。

> 然后可以使用`unzip`命令解压。

```sh
unzip Agave.zip
```
> 返回上一级目录，然后将上面创建的存放字体的目录移动到系统字体目录中。(这一步需要root权限)
```sh
cd ..
sudo mv AgaveNerd /usr/share/fonts
```
> 更新字体
```sh
fc-cache -vf
```
> 到这一步就已经成功安装`Agave Nerd Font`了。


### Windows系统
> 如果您使用的是windows系统

> 下载nerd font后将其解压，以我下载的`Agave Nerd Font`为例，下载好后是一个`Agave.zip`文件，
先将文件解压。
>
> 解压后进入到文件夹中，鼠标左键全选，然后点击右键，选择`安装`即可安装字体。
>
> 然后将使用的终端的字体设置为任意一种`Nerd Font`即可。

