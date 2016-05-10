# huniq

Simplified version of the uniq(1) tool, that uses a hash
table internally to remove and count duplicates.

# usage

  `$ huniq [-c|--count] [-h|--help] < FILE > FILE`

-c and --count can be used to indicate that duplicate elements should be
counted.
-h and --help will display this help page

# why?

This is useful for replacing the `sort | uniq -c` pattern
in cases where the input is very large (larger than ram)
but the uniqed output is mach smaller:

The sort step above needs to load the entire input data into
memory, so the amount of memory is roughly equal to the size
of the input data. huniq already deduplicates the data in
memory, so it's memory requirement is roughly equal to that
of the deduped output.

Note that huniq generally has no advantage to just using
`uniq` without the sort, since uniq just removes consecutive
duplicates so it just needs to keep a single line in memory.

huniq returns the input data in arbitrary order.

# building

Just type `make`. Move the resulting binary to a place of
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

