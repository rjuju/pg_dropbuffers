/*-------------------------------------------------------------------------
 *
 * pg_dropbuffers.c
 *
 * This program is open source, licensed under the PostgreSQL license.
 * For license terms, see the LICENSE file.
 *
 *-------------------------------------------------------------------------
 */


#include <sys/wait.h>
#include <unistd.h>

#include "postgres.h"

#include "miscadmin.h"
#include "storage/bufmgr.h"


PG_MODULE_MAGIC;

/*--- Functions --- */

void		_PG_init(void);
void		_PG_fini(void);

PG_FUNCTION_INFO_V1(pg_drop_current_db_buffers);
Datum		pg_drop_current_db_buffers(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pg_drop_system_cache);
Datum		pg_drop_system_cache(PG_FUNCTION_ARGS);

void
_PG_init(void)
{
	/* nothing */
}

void
_PG_fini(void)
{
	/* nothing */
}

Datum
pg_drop_current_db_buffers(PG_FUNCTION_ARGS)
{
	FlushDatabaseBuffers(MyDatabaseId);
	/* buffers can still be dirty here */
	DropDatabaseBuffers(MyDatabaseId);
    elog(LOG, "dropped shared buffers");

	PG_RETURN_VOID();
}

Datum
pg_drop_system_cache(PG_FUNCTION_ARGS)
{
    int exit_code;
    int pid = fork();
    if(pid == 0)
    {
        sync();
        execl("/usr/bin/sudo", "/usr/bin/sudo", "/sbin/sysctl", "vm.drop_caches=3", NULL);
        /* never executed; just to silence the compiler */
    }
    else
    {
        waitpid(pid, &exit_code, 0);
        if(exit_code == 0)
        {
            elog(LOG, "dropped system cache");
        }
        else
        {
            ereport(
                ERROR,
                (
                    errcode(ERRCODE_SYSTEM_ERROR),
                    errmsg("dropping system cache failed with return code %d", exit_code),
                    errhint("Make sure the user running postgresql is allowed to run the command `/usr/bin/sudo /sbin/sysctl vm.drop_caches=3`")
                )
            );
        }
    }
    PG_RETURN_VOID();
}
