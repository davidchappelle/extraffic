extraffic
=========

Extraffic is a suite of network traffic tools. The tools allow you to dissect
single a flow packet capture into a json based format that can be labelled and
stored away into a database. The traffic generation tool(s) operate based on the
database of json formatted flows. These flows can be permuted to provide a
permutation of traffic based on the definition of a single flow.

Unit Testing
============

cxxtest is integrated with this project. To install cxxtest in your development
environment you can try to install first from your package manager. For example:

    sudo apt-get install cxxtest

If your package manager cannot find a cxxtest package you will need to install
from source. First get the latest cxxtest version which you can find at the
following site:

    http://sourceforge.net/projects/cxxtest/files/cxxtest/

Unfortunately, installing from the cxxtest source isn't very user friendly. As
a result, you will need to perform a few manual steps. By following the steps
below, you will be able to update cxxtest fairly easily while maintaining
previous installations:

    $ gunzip cxxtest-<version>.tar.gz
    $ tar xf cxxtest-<version>.tar
    $ sudo cp -r cxxtest-<version>/cxxtest /usr/local/include/cxxtest-<version>
    $ sudo cp cxxtest-<version>/bin/cxxtestgen /usr/local/bin/cxxtestgen-<version>
    $ sudo ln -s /usr/local/include/cxxtest-<version> /usr/local/include/cxxtest
    $ sudo ln -s /usr/local/bin/cxxtestgen-<version> cxxtestgen

You should now be able to build your projects unit tests:

    $ make test

Third Party Requirements
========================

You will need to install libjsoncpp:

    apt-get install libjsoncpp-dev

