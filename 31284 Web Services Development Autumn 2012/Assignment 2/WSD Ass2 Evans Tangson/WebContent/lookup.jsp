<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="javax.xml.transform.stream.*"%>
<%@page import="javax.xml.transform.*"%>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>

	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<style type="text/css" media="all">@import "style.css";</style>
		<title>Lookup Web Application</title>
	</head>

	<body>
	<h1>Lookup Web Application</h1>
	<p>This one page web application uses JSP and XSLT to retrieve results from the 'lookup'
	RESTful Web Service.</p>
	
	<form METHOD="POST" ACTION="lookup.jsp">
		<p>Select a table: 
			<select NAME="lookup">
				<option VALUE="administrative_division">administrative_division
				<option VALUE="nametype">nametype
				<option VALUE="designation">designation
			</select>
		<input TYPE="SUBMIT" VALUE="Perform Lookup"></p>
	</form>
	
	<%
	String lookup = request.getParameter("lookup");
	if (lookup != null) {
	%>
	
	<h2>Results: "<%= lookup %>" table</h2>
		
	<%	try {
		// Load StreamSource objects with XML and XSLT files
		StreamSource xmlSource = 
			new StreamSource( "http://www-student.it.uts.edu.au/~brookes/gns/lookup/" +lookup );
		StreamSource xsltSource = 
		    new StreamSource( application.getResourceAsStream( "/lookup.xsl" ) );
			
		// Create a StreamResult pointing to the output file 
	    StreamResult fileResult = new StreamResult( out );
	 	
		// Load a Transformer object and perform the transformation
		TransformerFactory tfFactory = TransformerFactory.newInstance();
      	Transformer tf = tfFactory.newTransformer(xsltSource);
       	tf.transform(xmlSource, fileResult);
	  	}
		catch (Exception e) { e.printStackTrace(); }
	} %>
	</body>
</html>