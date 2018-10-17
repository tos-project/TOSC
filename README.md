TOSC Core integration/staging tree
=====================================

https://www.tosblock.com

What is TOSC?
---------------------

TOSC is a kind of digital coin which has been based on block-chain technology and aiming the new payment market by digital(virtual) currency system.

Many types of digital coin have issued world-widely in recent years, however any digital coins have not been practical for economical or financial usage but booming up only on dealing themselves by each other, that means the values of almost coins are ‘just possession’ such as old stamps, antique or jewelry. It’s non-sense!

Because we would be faced with emerging cashless world before long, we have prepared to create the new digital currency which should be safer, swifter and smarter in paying process on real commercial market. 
TOSC could substitute intelligent paying method for cash, plastic card (credit / debit) and all the other pay-system, so would pursue the lower paying-cost (commission) and shorter term for paying the money to affiliated store, it might be a win-win model between the customers and the affiliated store owners. That’s enough!

Visit https://www.tosblock.com for further information about the TOSC.

License
-------

TOSC Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development Process
---------------------

The master branch is regularly built and tested, but is not guaranteed to be completely stable. Tags are created regularly to indicate new official, stable release versions of TOSC Core.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

Translations
------------

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to TOSC periodically.

Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging messages are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play toscs" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode, blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

TOSC Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of which locks
are held, and adds warnings to the debug.log file if inconsistencies are detected.
