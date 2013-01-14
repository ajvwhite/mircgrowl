# mircgrowl #

A Growl for Windows Notifier plugin for popular IRC client mIRC

## Table of Contents ##
* [About the repository][aboutrepo]
* [How to use?][howtouse]
* [About the author][aboutauthor]

<a name="aboutrepo" />  

[aboutrepo]: #aboutrepo
## About this repository ##

This repository is a Microsoft Visual Studio project that creates a mIRC .dll when compiled. This DLL in combination with a mIRC script will notify you on the following events:

- When your nickname is mentioned
- When you receive a private message
- When a file send completes
- When a file is received successfully
- When a file send fails
- When a file receipt fails

The DLL is written in it's current instance to work of files in the %APPDATA%/mIRC/ folder (the default location mIRC stores your files).

<a name="howtouse" />

[howtouse]: #howtouse
## How to utilise the DLL ##

Once the DLL is compiled, take the following steps (using the mIRC help as a guide if you are unsure):

1. Copy the assets/icon/mirc-logo.png file to the %APPDATA%/mIRC/ folder
2. Copy the assets/growl-notify-mrc/growl-notify.mrc to your %APPDATA%/mIRC/ folder
3. Make any edits you wish to to the growl-notify.mrc script you have just copied
4. Copy the mircgrowl.dll you have compiled to %APPDATA%/mIRC/
5. Open mIRC
6. In a window type: `/load -rs growl-notify.mrc` (This should load the mrc script)
7. You should be ready to go, the first time the DLL is triggered the DLL should auto load and register itself with Growl

If you have any issues you may need to load the DLL pre-emptively, check the mIRC help on how to do this.

<a name="aboutauthor" />

[aboutauthor]: #aboutauthor
## About the author ##

The *mircgrowl* mIRC growl for windows plugin was originally written by me (Alexander White) as a personal project, if you wish to extend or improve this code please feel free to submit pull requests and I'd be happy to add them for everyone's benefit.
   
Special thanks to these technologies and those who produce them:  

* [mIRC](http://www.mirc.co.uk/)
* [Growl for windows](http://www.growlforwindows.com/gfw/)
* [Growl](http://growl.info/)