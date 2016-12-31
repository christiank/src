package.path = "/home/charlotte/devel/netbsd/lib/lua/kqueue/?.so;" .. package.path
require('kqueue')

kqueue.hello()
