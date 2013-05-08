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