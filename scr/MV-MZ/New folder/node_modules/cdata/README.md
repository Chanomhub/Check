cdata
=====

[![build status](https://travis-ci.org/charto/cdata.svg?branch=master)](http://travis-ci.org/charto/cdata)
[![npm version](https://img.shields.io/npm/v/cdata.svg)](https://www.npmjs.com/package/cdata)

This is a library of generic and efficient data structures written in TypeScript.
Currently only one is provided.

`BinaryHeap`
------------

This is a classic binary heap with O(lon(n)) insert, delete-min and decrease-key
(assuming a min-heap). The comparison function is user-provided to support a
min-heap or max-heap of arbitrary items.

License
=======

[The MIT License](https://raw.githubusercontent.com/charto/cdata/master/LICENSE)

Copyright (c) 2017- BusFaster Ltd
