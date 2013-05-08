/* Assignment 1 - David Evans - 10601514 - devans
Purpose: to clean the data from the helens_data table and migrate it to either 
dbp_clients or dbp_client_exceptions. */

-- (STEP 1) To execute the program:
DECLARE
BEGIN
clean_helens_data;
END;

-- (STEP 2) To view all records of the new dbp_clients table (successfully processed):
select id, fname, surname, companyname, streetnumber, streetname, suburb, postcode
from dbp_clients
order by streetname asc;

-- (STEP 3) To view all records of the new dbp_client_exceptions table (unsuccessfully processed):
select id, fname, surname, companyname, streetnumber, streetname, suburb, postcode, comments
from dbp_client_exceptions
order by streetname asc;

-- (STEP 4) To commit changes to the database, making them persistent:
COMMIT;

-- (OPTIONAL) To clear all records from the new tables:
TRUNCATE TABLE dbp_clients;
TRUNCATE TABLE dbp_client_exceptions;


/* CAUTION: Changes to the source code below will affect the execution of the 
program.  Reading the code may help you to understand the program execution. 
The code can be modified and recompiled to maintain/enhance the program. */

/* Procedure: clean_helens_data: transforms the data by running the below 
functions, inserting valid records into dbp_clients table and invalid records 
into dbp_client_exceptions table with comments detailing the rejection. */
CREATE OR REPLACE PROCEDURE clean_helens_data
AS
BEGIN

INSERT
WHEN (resolve_pobox(street1) IS NOT NULL AND resolve_postcode(suburb) IS NOT NULL) THEN
  INTO dbp_clients (id, fname, surname, companyname, streetname, suburb, postcode)
  VALUES (id, fname, surname, company, resolve_pobox(street1), suburb, resolve_postcode(suburb))
  
WHEN (resolve_corner(street1) IS NOT NULL AND resolve_postcode(suburb) IS NOT NULL) THEN
  INTO dbp_clients (id, fname, surname, companyname, streetname, suburb, postcode)
  VALUES (id, fname, surname, company, resolve_pobox(street1), suburb, resolve_postcode(suburb))
  
WHEN (resolve_streetnumber(street1) IS NOT NULL AND resolve_streetname(street1) IS NOT NULL AND resolve_postcode(suburb) IS NOT NULL) THEN
  INTO dbp_clients (id, fname, surname, companyname, streetnumber, streetname, suburb, postcode)
  VALUES (id, fname, surname, company, resolve_streetnumber(street1), resolve_streetname(street1), suburb, resolve_postcode(suburb))

WHEN (resolve_pobox(street1) IS NOT NULL AND resolve_postcode(suburb) IS NULL) THEN
  INTO dbp_client_exceptions (id, fname, surname, companyname, streetname, suburb, comments)
  VALUES (id, fname, surname, company, resolve_pobox(street1), suburb, 'Postcode could not be determined')
  
WHEN (resolve_corner(street1) IS NOT NULL AND resolve_postcode(suburb) IS NULL) THEN
  INTO dbp_client_exceptions (id, fname, surname, companyname, streetname, suburb, comments)
  VALUES (id, fname, surname, company, resolve_pobox(street1), suburb, 'Postcode could not be determined')
  
WHEN (resolve_streetnumber(street1) IS NOT NULL AND resolve_streetname(street1) IS NOT NULL AND resolve_postcode(suburb) IS NULL) THEN
  INTO dbp_client_exceptions (id, fname, surname, companyname, streetnumber, streetname, suburb, comments)
  VALUES (id, fname, surname, company, resolve_streetnumber(street1), resolve_streetname(street1), suburb, 'Postcode could not be determined')
  
ELSE
  INTO dbp_client_exceptions (id, fname, surname, companyname, streetname, suburb, postcode, comments)
  VALUES (id, fname, surname, company, street1, suburb, resolve_postcode(suburb), 'Address pattern was not recognised')

SELECT id, fname, surname, company, street1, suburb, resolve_corner(street1), resolve_pobox(street1), resolve_streetnumber(street1), resolve_streetname(street1), resolve_postcode(suburb)
FROM HELENS_DATA;

EXCEPTION
WHEN OTHERS THEN
      raise_application_error(-20001,'An error was encountered - '||SQLCODE||' -ERROR- '||SQLERRM);
END;

/* Function: resolve_corner(address_in): returns streetname value for valid Cnr 
addresses */
CREATE OR REPLACE FUNCTION resolve_corner
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetname varchar2(35) := '';
  streetnamepattern varchar2(160) := '([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd|Cl(ose)?)';
  
  cursor c1 is
    select regexp_substr(STREET1, 'C(n|orne)r '||streetnamepattern||' \& '||streetnamepattern)
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

/* Function: resolve_pobox(address_in): returns streetname value for valid PO 
Box addresses */
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

/* Function: resolve_street_number(address_in): returns streetnumber value for 
valid regular addresses  */
CREATE OR REPLACE FUNCTION resolve_streetnumber
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetnumber varchar2(10) := '';
  streetnumberpattern varchar(200) := '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2} ';
  streetnamepattern varchar2(160) := '([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd|Cl(ose)?)';
  fulladdresspattern varchar(280) := '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2}'||streetnamepattern;

/* Note: When address_in has a streetnumber component larger than the 
destination field (10 bytes), this function returns null */
  cursor c1 is
    select  substr(regexp_substr(STREET1, streetnumberpattern),1,10)
    from    helens_data
    where   street1 = address_in
    and     regexp_like(STREET1, fulladdresspattern)
    and     length(regexp_substr(STREET1, streetnumberpattern)) < 11;
  
BEGIN

open c1;
fetch c1 into streetnumber;
if c1%notfound then
    streetnumber := '';
end if;
close c1;

RETURN streetnumber;

EXCEPTION
WHEN OTHERS THEN
    raise_application_error(20001,'An error was encountered - '||SQLCODE||' -ERROR '||SQLERRM);
END;

/* Function: resolve_street_name(address_in): returns streetname value for 
valid regular addresses  */
CREATE OR REPLACE FUNCTION resolve_streetname
  ( address_in IN varchar2 )
  RETURN varchar2
IS
  streetname varchar2(35) := '';
  streetnamepattern varchar2(160) := '([[:alpha:]]{2,} )+(St(reet)?|R(oa)?d|Ave(nue)?|Dr(ive)?|H(w|ighwa)y|Lane|P(ara)?de|Pl(ace)?|Cres(cent)?|Boulevard|Blvd|Cl(ose)?)';
  fulladdresspattern varchar(280) := '((Shop|U(nit)?|Level|Lot) )?(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?)(([[:digit:]]+([[:alpha:]]| [[:alpha:]])?)(/|-| )?){0,2}'||streetnamepattern;

  cursor c1 is
    select regexp_substr(STREET1, streetnamepattern)
    from helens_data
    where street1 = address_in
    and   regexp_like(STREET1, fulladdresspattern);
  
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

/* Function: resolve_postcode(suburb_in): returns postcode value for valid 
suburbs  */
CREATE OR REPLACE FUNCTION resolve_postcode
  ( suburb_in IN varchar2 )
  RETURN varchar2
IS
  postcode varchar2(4);

/* Note: When suburb_in has more or less than one matching postcode, this 
function returns null */
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