/*-------------------------------------------------------------------------
 *
 * pg_dropbuffers.c
 *
 * This program is open source, licensed under the PostgreSQL license.
 * For license terms, see the LICENSE file.
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "miscadmin.h"
#include "storage/bufmgr.h"


PG_MODULE_MAGIC;

/*--- Functions --- */

void		_PG_init(void);
void		_PG_fini(void);

PG_FUNCTION_INFO_V1(pg_drop_current_db_buffers);
Datum		pg_drop_current_db_buffers(PG_FUNCTION_ARGS);

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

	PG_RETURN_VOID();
}
