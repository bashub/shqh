bin_PROGRAMS=shqh

shqh_SOURCES=shqh.c shqh_leveldb.c shqh_file.c


TESTS=check_leveldb
check_PROGRAMS=check_leveldb
check_leveldb_SOURCES=test_leveldb.c shqh_leveldb.c
check_leveldb_CFLAGS = @CHECK_CFLAGS@
check_leveldb_LDADD = @CHECK_LIBS@

