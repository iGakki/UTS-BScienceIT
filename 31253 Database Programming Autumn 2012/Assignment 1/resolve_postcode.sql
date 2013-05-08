CREATE OR REPLACE FUNCTION resolve_postcode
  ( suburb_in IN varchar2 )
  RETURN varchar2
IS
  postcode varchar2(4);

  cursor c1 is
    select postcode
    from dbp_postcode
    where locality = suburb_in
    and locality IN (
        SELECT    locality
        FROM      DBP_POSTCODE
        GROUP BY  locality
        HAVING    count(locality) = 1
        );

-- The cursor excludes localities with more than one matching postcode

BEGIN

open c1;
fetch c1 into postcode;

if c1%notfound then
    postcode := '';
end if;

close c1;

RETURN postcode;

EXCEPTION
WHEN OTHERS THEN
    raise_application_error(20001,'An error was encountered - '||SQLCODE||' -ERROR '||SQLERRM);
END;