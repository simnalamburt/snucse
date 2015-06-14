Swaptions
========
```sh
version=seq make
thorq --add ./swaptions -ns 128 -sm 1000000
```
```sh
version=pthreads make
thorq --add ./swaptions -ns 128 -sm 1000000 -nt 16
```

--------
Copyright (c) 2007 Intel Corp
