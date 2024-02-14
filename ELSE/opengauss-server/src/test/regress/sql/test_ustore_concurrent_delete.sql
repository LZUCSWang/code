-- for concurrent delete
-- test case: commit, delete same records
create table z1 (c1 int) with (storage_type=USTORE);

insert into z1 values (1);
insert into z1 values (2);
insert into z1 values (3);
insert into z1 values (4);
insert into z1 values (5);
insert into z1 values (6);

\parallel on 2

declare
	cnt int;
begin
	delete from z1 where c1=1;
	perform pg_sleep(1);
	delete from z1 where c1=2;
	select count(*) into cnt from z1;
	if cnt != 4 then
		raise notice 'ERROR: worker 1 expect cnt = %, but %', 4, cnt;
	end if;
end;
/

declare
	cnt int;
begin
	perform pg_sleep(1);
	delete from z1 where c1=1;
	perform pg_sleep(1);
	select count(*) into cnt from z1;
	if cnt != 4 then
		raise notice 'ERROR: worker 2 expect cnt = %, but %', 4, cnt;
	end if;
	delete from z1 where c1=2;
	
end;
/

\parallel off

select * from z1 order by c1; -- should be 3, 4, 5, 6

drop table z1;

-- test case: commit, delete different records
create table z1 (c1 int) with (storage_type=USTORE);

insert into z1 values (1);
insert into z1 values (2);
insert into z1 values (3);
insert into z1 values (4);
insert into z1 values (5);
insert into z1 values (6);

\parallel on 2
declare
	cnt int;
begin
	delete from z1 where c1=1;
	perform pg_sleep(1);
	delete from z1 where c1=2;
	perform pg_sleep(1);
	select count(*) from z1 into cnt;
	if cnt != 4 then
		raise notice 'ERROR: worker 1 expect cnt = %, but %', 4, cnt;
	end if;
end;
/

declare
	cnt int;
begin
	perform pg_sleep(1);
	delete from z1 where c1=3;
	perform pg_sleep(2);
	delete from z1 where c1=4;
	select count(*) from z1 into cnt;
	if cnt != 2 then
		raise notice 'ERROR: worker 2 expect cnt = %, but %', 2, cnt;
	end if;
end;
/

\parallel off

select * from z1 order by c1; -- should be 5, 6

drop table z1;


