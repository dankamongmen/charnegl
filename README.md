# Charn
by Nick Black (dankamongmen@gmail.com)

![image](doc/charn.gif)

>It is silent now. But I have stood here when the whole air was full of the
>noises of Charn; the trampling of feet, the creaking of wheels, the cracking of
>the whips and the groaning of slaves, the thunder of chariots, and the
>sacrificial drums beating in the temples. I have stood here (but that was near
>the end) when the roar of battle went up from every street and the river of
>Charn ran red. All in one moment one woman blotted it out forever.
>
> C.S. Lewis, *The Magician's Newphew*

## Requirements

* CMake 3.2+ and C++ development tools
* libconfig ([http://www.hyperrealm.com/libconfig/libconfig_manual.html])
* DocBook XSL and xsltproc, for man pages

On Debian-derived systems, this includes:

* build-essential
* cmake
* libconfig++-dev
* docbook-xsl
* xsltproc

## Building

* mkdir build && cd build && cmake .. && make && sudo make install

## Testing

Within an existing X session, it's best to use Xephyr. Xnest does not provide
a sufficient xrandr implementation.

## Reading

* https://nick-black.com/blog/0014-new-directions-in-window-management-p1.html
* https://nick-black.com/blog/0015-new-directions-in-window-management-p2.html
