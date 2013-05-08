CREATE OR REPLACE FUNCTION resolve_pobox
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetname varchar2(35) := '';
  tempstreetname varchar2(35) := '';

  cursor c1 is
    select  regexp_substr(street1, 'PO Box [[:digit:]]+')
    from helens_data
    where street1 = address_in;
  
BEGIN

open c1;
fetch c1 into streetname;
if c1%notfound then
    streetname := '';
end if;
close c1;

RETURN streetname;

EXCEPTION
WHEN OTHERS THEN
    raise_application_error(20001,'An error was encountered - '||SQLCODE||' -ERROR '||SQLERRM);
END;