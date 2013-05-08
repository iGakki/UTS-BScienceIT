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
public StreamSource getLookupXmlStream( String type, String value ) {
	return new StreamSource( "http://www-student.it.uts.edu.au/~brookes/gns/lookup/" + type + "/" + value );
}

public StreamSource getFeaturesXmlStream( String ufi ) {
	return new StreamSource( "http://www-student.it.uts.edu.au/~brookes/gns/location/" +ufi);
}

public StreamSource getXslStream( String xsl, ServletContext application ) {
	return new StreamSource( application.getResourceAsStream( xsl ) );
}

public void transform( StreamSource xmlSource, StreamSource xsltSource, JspWriter out)
{
	try {
		// Create a StreamResult pointing to the output file 
	    StreamResult fileResult = new StreamResult( out );
	 	
		// Load a Transformer object and perform the transformation
		TransformerFactory tfFactory = TransformerFactory.newInstance();
      	Transformer tf = tfFactory.newTransformer( xsltSource );
       	tf.transform( xmlSource, fileResult );
  	}
	catch ( Exception e ) { e.printStackTrace(); }
}
%>

<% 
String ufi = request.getParameter("ufi");
String adm = request.getParameter("adm");
String des = request.getParameter("des");
String ntype = request.getParameter("type");
String full = request.getParameter("full");
String mod = request.getParameter("mod");
%>

<h1>Features Web Application</h1>
<h2>Feature in detail:</h2>
<table>
	<tr><td width="150px">Full Name:</td><td><%= full %></td></tr>
	<tr><td>Designation:</td><td><%	transform( getLookupXmlStream( "designation", des ), 
					getXslStream( "description.xsl", application ), out); %></td></tr>
	<tr><td>Administrative Division:</td><td><%	transform( getLookupXmlStream( "administrative_division", adm ), 
					getXslStream( "description.xsl", application ), out); %></td></tr>
	<tr><td>Name Type:</td><td><%	transform( getLookupXmlStream( "nametype", ntype ), 
					getXslStream( "description.xsl", application ), out); %></td></tr>
	<tr><td>Modified:</td><td><%= mod %></td></tr>
</table>

<%
transform( getFeaturesXmlStream( ufi ), getXslStream( "detail.xsl", application ), out);
%>
</body>
</html>