pg_dropbuffers
==============

Small PostgreSQL extension to drop buffers from shared_buffers without having to
restart your cluster.

Obviously, this is just for testing purpose, you **should not** use this
extension on a production server, unless you want to ruin the performance, and
have other very bad things happen.

Functions provided
------------------

**pg_drop_current_db_buffers**: Drop all buffers of current database.  **Be
careful that any dirty buffers won't get flushed to disk before removing.  You
can therefore lose data**.

**pg_drop_system_cache**: Drop the system cache. Note that you must allow the
user postgres runs as to do it without password, by adding this line in your
sudoers file:

```POSTGRESUSER ALL=NOPASSWD: /sbin/sysctl vm.drop_caches=3```

This function will return void if the system cache was dropped succesfully, and
will throw an error if it failed.

**pg_drop_caches**: Wrapper for dropping both the shared buffers and the system
cache.

Usage
-----

```sql
SELECT pg_drop_current_db_buffers();
SELECT pg_drop_system_cache();
SELECT pg_drop_caches();
```

Installation instructions
-------------------------

Compile and install the extension:
```sh
PATH=/path/to/pg/bin:$PATH make
PATH=/path/to/pg/bin:$PATH sudo make install
```

Then in psql:
```
CREATE EXTENSION pg_dropbuffers;
```
