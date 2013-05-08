<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@page import="javax.xml.transform.stream.*"%>
<%@page import="javax.xml.transform.*"%>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>

<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<style type="text/css" media="all">
		@import "style.css";
	</style>
	<title>Features Web Application</title>
</head>

<body>

<%!
public StreamSource getLookupXmlStream( String type ) {
	return new StreamSource( "http://www-student.it.uts.edu.au/~brookes/gns/lookup/" + type + "/" );
}

public StreamSource getFeaturesXmlStream( String name, String desig, String admin ) {
	return new StreamSource( "http://www-student.it.uts.edu.au/~brookes/gns/features/name/" 
			+ name + "/designation/" + desig + "/administrative_division/" + admin );
}

public StreamSource getXslStream( String xsl, ServletContext application ) {
	return new StreamSource( application.getResourceAsStream( xsl ) );
}

public void transform( StreamSource xmlSource, StreamSource xsltSource, JspWriter out, String sort, String order, String pageNum, String name, String desig, String admin)
{
	try {
		// Create a StreamResult pointing to the output file 
	    StreamResult fileResult = new StreamResult( out );
	 	
		// Load a Transformer object and perform the transformation
		TransformerFactory tfFactory = TransformerFactory.newInstance();
      	Transformer tf = tfFactory.newTransformer( xsltSource );
      	tf.setParameter("sort", sort ); // Edit XSL sort parameter here
      	tf.setParameter("order", order ); // Edit XSL order parameter here
      	tf.setParameter("Page", pageNum);
        tf.setParameter("name", name);
        tf.setParameter("desig", desig);
        tf.setParameter("admin", admin);
       	tf.transform( xmlSource, fileResult );
  	}
	catch ( Exception e ) { e.printStackTrace(); }
}
%>
	
<h1>Features Web Application</h1>

<p>This web application uses JSP and XSLT to retrieve results from the 'features'
RESTful Web Service.</p>

<form METHOD="GET" ACTION="index.jsp">
	<input type="hidden" name="hide" value="yes">
	<input type="hidden" name="page" value="0">
	<input type="hidden" name="pagesize" value="1">
	<table>
		<tr>
			<td>Name:</td>
			<td><input type="text" name="name" size="20"></td>
		</tr>		
		<tr>
			<td>Designation:</td>
			<td><SELECT NAME="designation">
			<%	transform( getLookupXmlStream( "designation" ), getXslStream( 
					"/index.xsl", application ), out, "", "", "0", "", "", ""); %></SELECT></td>
		</tr>
		<tr>
			<td>Administrative Division:</td>
			<td><SELECT NAME="administrative_division">
			<%	transform( getLookupXmlStream( "administrative_division" ), 
					getXslStream( "/index.xsl", application ), out, "", "", "0", "", "", ""); %></SELECT></td>
		</tr>
		<tr>
			<td>Sort by:</td>
			<td>
				<SELECT NAME="sort">
					<option value="">--- Please select ---</option>
					<option value="designation">Designation</option>
					<option value="administrative_division">Administrative Division</option>
					<option value="modified">Date Modified</option>
				</SELECT></td>
		</tr>
		<tr>
			<td>Order:</td>
			<td>
				<SELECT NAME="order">
					<option value="">--- Please select ---</option>
					<option value="ascending">Ascending</option>
					<option value="descending">Descending</option>
				</SELECT></td>
		</tr>
		<tr><td><input TYPE="SUBMIT" VALUE="Find features"></td></tr>
	</table>
</form>

<%	
String hide = request.getParameter("hide");
if (hide != null)
{
String name = request.getParameter("name");
String desig = request.getParameter("designation");
String admin = request.getParameter("administrative_division");
String sort = request.getParameter("sort");
String order = request.getParameter("order");
String	 pages = request.getParameter("page");
String pagesize = request.getParameter("pagesize");

if ( name.matches( ".*[a-zA-Z0-9]+.*" ) || admin != "" && admin != null || 
	desig != "" && desig != null ) { %>

	<h2>Features found:</h2>

<%
	transform( getFeaturesXmlStream ( name, desig, admin ), getXslStream( 
			"/features.xsl", application ), out, sort, order, pages, name, desig, admin );
}
else { %>
	<p>Oops! You need at least one search parameter - try again.</p>
<% }
}
%> <!-- Close else section -->

</body>
</html>