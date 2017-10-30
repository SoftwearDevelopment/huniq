# huniq

Simplified version of the basic usages ofuniq(1) and sort(1),
that uses a hash table internally to remove and count duplicates.

# usage

  `$ huniq [-c|--count] [-h|--help] < FILE > FILE`

-c and --count can be used to indicate that duplicate elements should be
counted.
-h and --help will display this help page

# why?

This is useful for replacing the `sort | uniq -c`, `sort | uniq` or `sort -u`
in cases where sorting is not required.

`huniq -c` and `huniq` are both generally faster and use less memory than
their counterparts, this is achieved by using a couple of optimizations:

A hash table is used to store duplicates instead of sorting the input;
this increases performance, since hashing is usually faster than sorting.
It also means that duplicates do not have to be stored individually (they
all occupy the same hash bucket), so the memory requirements grow with the
size of the output and not the input. E.g. if each line in the input has a
one duplicate at average, we need 50% less memory.

`huniq` also does not store the actual lines themselves, instead it just stores
a hash value (16 byte each) of that line. This is especially very useful when very
long lines are in the input.

`huniq` outputs lines in the order they where given, while `huniq -c` returns lines
in arbitrary order.

huniq does not swap data to disk like gnu sort does, so for that reason it sometimes
also uses more memory than sort, especially when there are many items and not many duplicates.

Note that huniq generally has no advantage to just using
`uniq` without the sort, since uniq just removes consecutive
duplicates so it just needs to keep a single line in memory.

# building

Download the submodules (`git submodule init && git submodule update`)
and then just type `make`. Move the resulting binary to a place of
your choosing in order to install.

# LICENSE

Written by (karo@cupdev.net) Karolin Varner, for Softwear, BV (http://nl.softwear.nl/contact):
You can still buy me a Club Mate. Or a coffee.

Copyright © (c) 2016, Softwear, BV.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the Karolin Varner, Softwear, BV nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Softwear, BV BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

