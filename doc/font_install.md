# Font installation
This project uses `nerd font`, make sure that the font used by the terminal is either `nerd font`.

If you don't have nerd font installed, go to [here](https://www.nerdfonts.com/) to download and install the font.
## For linux
> If you are using Linux:
>
> You can use the following command to view the fonts that have been installed:
```sh
fc-list | less
```

> If you have nerdfont, set the font of the terminal to any nerdfont.
>
> If not, after downloading your favorite nerdfont in the address provided above, first extract the font file, here take the `Agave Nerd Font` I downloaded as an example, the downloaded file is `Agave.zip`.
> First, we'll create a directory to store our fonts, here let's create an AgaveNerd directory as an example.

```sh
mkdir AgaveNerd
```
> Then move the font file you just downloaded to the created directory. Then go to the directory
```sh
mv Agave.zip AgaveNerd &&cd AgaveNerd
```
> To extract the `zip` format of the compressed package requires the `unzip` command, if you do not have the `unzip` command, download the `unzip` command first. If so, skip the paragraph first.


> If your Linux is a Debian-based system, you can install it using the following command:
```sh
sudo apt install unzip
```
> If your system is based on Red Hat, you can install it using the following command:
```sh
sudo yum install unzip
```
> If your system is Arch, you can install it using the following command:
```sh
sudo pacman -S unzip
```
> For other Linux distributions, you can go to the [official website] (https://infozip.sourceforge.net/) of unzip and download and install them yourself.
> can then be unzipped using the `unzip` command.
```sh
unzip Agave.zip
```

> Return to the previous directory, and then move the directory created above to store the fonts to the system font directory. (This step requires root access)
```sh
cd ..
sudo mv AgaveNerd /usr/share/fonts
```
> update fonts
```sh
fc-cache -vf
```
> At this point, `Agave Nerd Font` has been successfully installed.


## For Windows
> If you are using a Windows system

> Download the nerd font and unzip it, take the `Agave Nerd Font` I downloaded as an example, it is an `Agave.zip` file after downloading,
>
> Extract the files first.
>
> After extracting, go to the folder, select all with the left mouse button, then right-click, and select `Install` to install the font.
>
> Then set the font of the terminal used to any of `Nerd Font`.

