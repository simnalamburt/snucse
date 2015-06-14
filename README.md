Swaptions
========
```sh
make version=seq
thorq --add ./bin -ns 128 -sm 1000000
```
```sh
make version=pthreads
thorq --add ./bin -ns 128 -sm 1000000 -nt 16
```

--------
Copyright (c) 2007 Intel Corp
