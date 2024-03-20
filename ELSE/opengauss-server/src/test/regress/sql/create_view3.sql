--
-- CREATE_VIEW3
--
-- Enforce use of COMMIT instead of 2PC for temporary objects

CREATE VIEW view_const AS SELECT 'abc';
SELECT * FROM view_const;
DROP VIEW view_const;

SET search_path to public;

CREATE SCHEMA DTS_STORAGE;

SET SEARCH_PATH TO DTS_STORAGE;
CREATE TABLE RULE_TABLE_001(COL_INT INTEGER);
CREATE TABLE RULE_TABLE_001_01(COL_INT INTEGER);

SELECT RELNAME,RELKIND FROM PG_CLASS WHERE RELNAME LIKE 'rule_table_001%' ORDER BY 1;
SELECT RELNAME, ATTNAME FROM PG_ATTRIBUTE A, PG_CLASS C WHERE C.OID = A.ATTRELID AND C.RELNAME LIKE 'rule_table_001%' ORDER BY 1, 2;
SELECT RELNAME, X.PCLOCATORTYPE, X.PGROUP FROM PGXC_CLASS X JOIN PG_CLASS C ON (C.OID = X.PCRELID) WHERE PCRELID IN (SELECT OID FROM PG_CLASS WHERE RELNAME LIKE 'rule_table_001%') ORDER BY 1;

CREATE RULE "_RETURN" AS ON SELECT TO RULE_TABLE_001 DO INSTEAD SELECT * FROM RULE_TABLE_001_01;

RESET SEARCH_PATH;
SELECT RELNAME,RELKIND FROM PG_CLASS WHERE RELNAME LIKE 'rule_table_001%' ORDER BY 1;
SELECT RELNAME, ATTNAME FROM PG_ATTRIBUTE A, PG_CLASS C WHERE C.OID = A.ATTRELID AND C.RELNAME LIKE 'rule_table_001%' ORDER BY 1, 2;
SELECT RELNAME, X.PCLOCATORTYPE, X.PGROUP FROM PGXC_CLASS X JOIN PG_CLASS C ON (C.OID = X.PCRELID) WHERE PCRELID IN (SELECT OID FROM PG_CLASS WHERE RELNAME LIKE 'rule_table_001%') ORDER BY 1;

DROP TABLE DTS_STORAGE.RULE_TABLE_001_01 CASCADE;

SET SEARCH_PATH TO DTS_STORAGE;
CREATE TABLE "RULE_TABLE_001"(COL_INT INTEGER);
CREATE TABLE "RULE_TABLE_001_01"(COL_INT INTEGER);

SELECT RELNAME,RELKIND FROM PG_CLASS WHERE RELNAME LIKE 'RULE_TABLE_001%' ORDER BY 1;
SELECT RELNAME, ATTNAME FROM PG_ATTRIBUTE A, PG_CLASS C WHERE C.OID = A.ATTRELID AND C.RELNAME LIKE 'RULE_TABLE_001%' ORDER BY 1, 2;
SELECT RELNAME, X.PCLOCATORTYPE, X.PGROUP FROM PGXC_CLASS X JOIN PG_CLASS C ON (C.OID = X.PCRELID) WHERE PCRELID IN (SELECT OID FROM PG_CLASS WHERE RELNAME LIKE 'RULE_TABLE_001%') ORDER BY 1;

CREATE RULE "_RETURN" AS ON SELECT TO "RULE_TABLE_001" DO INSTEAD SELECT * FROM "RULE_TABLE_001_01";

RESET SEARCH_PATH;
SELECT RELNAME,RELKIND FROM PG_CLASS WHERE RELNAME LIKE 'RULE_TABLE_001%' ORDER BY 1;
SELECT RELNAME, ATTNAME FROM PG_ATTRIBUTE A, PG_CLASS C WHERE C.OID = A.ATTRELID AND C.RELNAME LIKE 'RULE_TABLE_001%' ORDER BY 1, 2;
SELECT RELNAME, X.PCLOCATORTYPE, X.PGROUP FROM PGXC_CLASS X JOIN PG_CLASS C ON (C.OID = X.PCRELID) WHERE PCRELID IN (SELECT OID FROM PG_CLASS WHERE RELNAME LIKE 'RULE_TABLE_001%') ORDER BY 1;

DROP SCHEMA DTS_STORAGE CASCADE;