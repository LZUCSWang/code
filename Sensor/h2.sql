-- 1
SELECT
    Member.mid,
    Member.mname
FROM
    Member
    JOIN BikeDriven ON Member.mid = BikeDriven.mid
    JOIN Bike ON BikeDriven.bname = Bike.bname
WHERE
    Bike.manuf = 'BMW';

-- 2
SELECT
    BikeDriven.bname
FROM
    BikeDriven
    JOIN Member ON BikeDriven.mid = Member.mid
WHERE
    Member.mname = 'Mike'
    AND BikeDriven.miles > 1000;

-- 3
SELECT
    Member.mname,
    Bike.bname,
    Bike.price
FROM
    Member
    JOIN BikeDriven ON Member.mid = BikeDriven.mid
    JOIN Bike ON BikeDriven.bname = Bike.bname
WHERE
    Bike.price = (
        SELECT
            MIN(price)
        FROM
            Bike
    );

--- 4
SELECT
    m.mname,
    SUM(bd.miles)
FROM
    Member m
    LEFT JOIN BikeDriven bd ON m.mid = bd.mid
GROUP BY
    m.mid,
    m.mname;

-- 5
SELECT DISTINCT
    bd.mid
FROM
    BikeDriven bd
    INNER JOIN Member m ON bd.mid = m.mid
WHERE
    bd.bname = m.favBike
    AND NOT EXISTS (
        SELECT
            1
        FROM
            BikeDriven bd2
        WHERE
            bd2.mid = bd.mid
            AND bd2.bname <> m.favBike
    );