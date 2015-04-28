# Tracebox

[![Build Status](https://travis-ci.org/tracebox/tracebox.png?branch=master)](https://travis-ci.org/tracebox/tracebox)

[Tracebox](http://www.tracebox.org) is a tool that allows to detect middleboxes on any paths, i.e., between a source and any destination. Tracebox can be viewed as a tool similar to traceroute as it uses ICMP replies to identify changes in the packets. The fact that tracebox is able to detect middleboxes comes from the observation that ICMP messages are often not as defined in RFC792. Indeed it is quite common to receive a ICMP Time-to-Live exceeded message with the original datagram instead of 64 bits as described in the standard. This is caused by operating systems configured to reply with full ICMP (e.g., Linux, Cisco IOS-XR, etc.) as well as the ICMP Multi-Part Messages extension that standardize the fact that routers using MPLS tunnels replies and ICMP message containing the full datagram.

## Install

### Mac OS X (Using Homebrew)

    brew install tracebox

### Linux

Requirements: autotools, automake, libtool, liblua-dev, libpcap-dev, libjson0, libjson0-dev, libcurl4-gnutls-dev

To build:

    $ ./bootstrap.sh
    $ ./configure [--prefix=install_prefix [--enable-tests][--enable-curl]]
    $ make
    # make install

### OpenWRT

The package is available at http://github.com/tracebox/openwrt.
Inside the OpenWRT SDK:

    $ echo "src-git tracebox git://github.com/tracebox/openwrt.git" >> feeds.conf.default
    $ ./scripts/feeds install -a tracebox
    $ make menuconfig # select tracebox in "Network"
    $ make package/tracebox/compile # should generate a package in bin/<target>/packages/tracebox_*.ipk

## Documentation
The Lua API is (should) be documented and is available at http://tracebox.org/lua_doc.
It can be generated using [LDoc](https://github.com/stevedonovan/LDoc) from the root directory (see config.ld):

    $ ldoc .

The documentation should be created under doc/

## JSON Format

More detailled information about the successive hops can be obtained using the -j option,
this will as well change the output mode to JSON

```javascript
{
    "addr"     : "IP of the destination",
    "name"     : "Name of the destination [Optional]",
    "max_hops" : "Number of maximum hops",
    "Hops"     : [ /* Array containing each hop information */
        {
            "hop"           : "Corresponding TTL/hop limit",
            "from"          : "IP address of that hop",
            "name"          : "Name of the hop [Optional]",
            "Modifications" : [
                // if tracebox was called with -v :
                    "Name of the modification" : {
                        "Expected" : "Value injected",
                        "Received" : "Value receveid"
                    },
                // else:
                    "Name of the modification"
            ],
            "Additions"    : [
                // if tracebox was called with -v :
                    {
                        "Name of the modification" : {
                            "Info": "Information added"
                        },
                    }
                // else:
                    "Name of the field(s) added"
            ],
            "Deletions"     : [
                // if tracebox was called with -v :
                    {
                        "Name of the modification" : {
                            "Info": "Information deleted"
                        },
                    }
                // else:
                    "Name of the field(s) deleted"
            ],
            "ICMPExtension" : /*[Optional]*/ [
                //if tracebox was called with -v :
                    {
                        "Name of the extension" : {
                            "Info": "Information of the extension"
                        }
                    },
                // else:
                    "Name of the extension(s)"

            ]
        }
    ]
}
```
