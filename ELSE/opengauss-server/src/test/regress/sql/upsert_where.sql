----
-- setup
----
CREATE SCHEMA schema_upsert_where;
SET search_path = schema_upsert_where;

----
-- basic syntax
----
CREATE TABLE tab_target1(c1 int unique, c2 int);
INSERT INTO tab_target1 VALUES(generate_series(1,10), generate_series(1,10));

CREATE TABLE tab_target2(c1 int unique, c2 int unique, c3 int);
INSERT INTO tab_target2 VALUES(generate_series(1,10), generate_series(1,10), generate_series(1,10));

CREATE TABLE tab_target3(c1 int, c2 int, c3 int, unique(c1, c2)) ;
INSERT INTO tab_target3 VALUES(generate_series(1,10), generate_series(1,10), generate_series(1,10));

CREATE TABLE tab_source(c1 int, c2 int, c3 int, c4 int);
INSERT INTO tab_source VALUES(generate_series(1,10), generate_series(10,1, -1), generate_series(1,10), generate_series(1,10));

begin;
-- no conflict where clause is ignored (of course)
INSERT INTO tab_target1 VALUES(0,0) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE false;
INSERT INTO tab_target1 VALUES(1,2) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 1;
SELECT * FROM tab_target1 ORDER BY 1,2;
INSERT INTO tab_target1 VALUES(1,3) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 + excluded.c2 = 5;
SELECT * FROM tab_target1 ORDER BY 1,2;

-- multiple values
INSERT INTO tab_target1 VALUES(2,3),(3,4) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 2;
SELECT * FROM tab_target1 ORDER BY 1,2;
INSERT INTO tab_target1 VALUES(3,4),(3,5),(3,6),(3,7),(3,8),(3,9) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 3;
SELECT * FROM tab_target1 ORDER BY 1,2;

-- from source table
INSERT INTO tab_target1 (SELECT c1, c2 FROM tab_source) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c1 > 5;
SELECT * FROM tab_target1 ORDER BY 1,2;

-- multiple confliction - where clause will not affect target row of upsert
INSERT INTO tab_target2 VALUES(1,2,10) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 = 1;
INSERT INTO tab_target2 VALUES(2,3,30) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 != 2;
SELECT * FROM tab_target2 ORDER BY 1,2,3;

-- multi-column unique constraint with coercion
INSERT INTO tab_target3 VALUES(1,1,10) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 < 5;
INSERT INTO tab_target3 VALUES(2,2,20) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c2 between 1 and 3;
INSERT INTO tab_target3 VALUES(3,3,30) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c2 = 3 and (c3 < 30 or c1 = 2) and (not (c1 between 20 and 30));
SELECT * FROM tab_target3 ORDER BY 1,2,3;

-- test pbe
PREPARE P1 AS INSERT INTO tab_target3 VALUES($1,$2,$3) ON DUPLICATE KEY UPDATE c3 = excluded.c3 + $4 WHERE c1 < $5;
EXECUTE P1(4, 4, 40, 4, 4);
SELECT * FROM tab_target3 ORDER BY 1,2,3;
EXECUTE P1(4, 4, 40, 4, 5);
SELECT * FROM tab_target3 ORDER BY 1,2,3;

----
-- test a_expr cases
----
INSERT INTO tab_target1 VALUES(0,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE NULL;
INSERT INTO tab_target1 VALUES(1,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 0::boolean;
INSERT INTO tab_target1 VALUES(2,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE false and true;
INSERT INTO tab_target1 VALUES(3,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 'abc' not like '%c';
INSERT INTO tab_target1 VALUES(4,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 1 IS NULL;
INSERT INTO tab_target1 VALUES(5,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 
    (timestamp with time zone '2000-11-26', timestamp with time zone '2000-11-27')
    OVERLAPS (timestamp with time zone '2000-11-27 12:00', timestamp with time zone '2000-11-30');
INSERT INTO tab_target1 VALUES(6,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 
    row(1,1) is distinct from row(1,1);
INSERT INTO tab_target1 VALUES(7,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 1 is unknown;
INSERT INTO tab_target1 VALUES(8,-1) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE 1 not in (1,2,3);
SELECT COUNT(*) FROM tab_target1 WHERE c2 = -1;
rollback;

-- explain analyze
begin;
EXPLAIN (ANALYZE ON, COSTS OFF, TIMING OFF) INSERT INTO tab_target1 VALUES(1,2) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 + excluded.c2 = 3;

EXPLAIN (ANALYZE ON, COSTS OFF, TIMING OFF) INSERT INTO tab_target1 VALUES(3,4),(3,5),(3,6),(3,7),(3,8),(3,9) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 3;

EXPLAIN (ANALYZE ON, COSTS OFF, TIMING OFF) INSERT INTO tab_target2 VALUES(1,2,10) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 = 1;

EXPLAIN (ANALYZE ON, COSTS OFF, TIMING OFF) INSERT INTO tab_target3 VALUES(3,3,30) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c2 = 3 and (c3 < 30 or c1 = 2) and (not (c1 between 20 and 30));

EXPLAIN (ANALYZE ON, COSTS OFF, TIMING OFF) EXECUTE P1(4, 4, 40, 4, 5);
rollback;
----
-- test with synonym
----
create synonym stt1 for tab_target1;
create synonym stt2 for tab_target2;
create synonym stt3 for tab_target3;
create synonym sts for tab_source;

begin;
-- no conflict where clause is ignored (of course)
INSERT INTO stt1 VALUES(0,0) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE false;
INSERT INTO stt1 VALUES(1,2) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 1;
SELECT * FROM stt1 ORDER BY 1,2;
INSERT INTO stt1 VALUES(1,3) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 + excluded.c2 = 5;
SELECT * FROM stt1 ORDER BY 1,2;

-- multiple values
INSERT INTO stt1 VALUES(2,3),(3,4) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 2;
SELECT * FROM stt1 ORDER BY 1,2;
INSERT INTO stt1 VALUES(3,4),(3,5),(3,6),(3,7),(3,8),(3,9) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c2 = 3;
SELECT * FROM stt1 ORDER BY 1,2;

-- from source table
INSERT INTO stt1 (SELECT c1, c2 FROM sts) ON DUPLICATE KEY UPDATE c2 = excluded.c2 WHERE c1 > 5;
SELECT * FROM stt1 ORDER BY 1,2;

-- multiple confliction - where clause will not affect target row of upsert
INSERT INTO stt2 VALUES(1,2,10) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 = 1;
INSERT INTO stt2 VALUES(2,3,30) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 != 2;
SELECT * FROM stt2 ORDER BY 1,2,3;

-- multi-column unique constraint
INSERT INTO stt3 VALUES(1,1,10) ON DUPLICATE KEY UPDATE c3 = excluded.c3 WHERE c1 < 5;
SELECT * FROM stt3 ORDER BY 1,2,3;

-- test pbe
deallocate p1;
PREPARE P1 AS INSERT INTO stt3 VALUES($1,$2,$3) ON DUPLICATE KEY UPDATE c3 = excluded.c3 + $4 WHERE c1 < $5;
EXECUTE P1(2, 2, 20, 2, 2);
SELECT * FROM stt3 ORDER BY 1,2,3;
EXECUTE P1(2, 2, 20, 2, 3);
SELECT * FROM tab_target3 ORDER BY 1,2,3;
rollback;



DROP SCHEMA schema_upsert_where CASCADE;
