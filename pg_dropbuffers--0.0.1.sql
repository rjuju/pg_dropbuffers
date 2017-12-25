-- This program is open source, licensed under the PostgreSQL License.
-- For license terms, see the LICENSE file.
--
-- Copyright (C) 2017: Julien Rouhaud

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_dropbuffers" to load this file. \quit

SET client_encoding = 'UTF8';

CREATE FUNCTION pg_drop_current_db_buffers()
    RETURNS void
    LANGUAGE c COST 100
AS '$libdir/pg_dropbuffers', 'pg_drop_current_db_buffers';

CREATE FUNCTION pg_drop_system_cache()
    RETURNS void
    LANGUAGE c COST 100
AS '$libdir/pg_dropbuffers', 'pg_drop_system_cache';

CREATE FUNCTION pg_drop_caches() RETURNS VOID AS $$
BEGIN
    PERFORM pg_drop_current_db_buffers();
    PERFORM pg_drop_system_cache();
END;
$$ LANGUAGE plpgsql;
