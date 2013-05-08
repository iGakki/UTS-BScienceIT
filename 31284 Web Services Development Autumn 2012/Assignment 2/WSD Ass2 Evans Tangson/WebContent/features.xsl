<?xml version="1.0" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
version="1.0">

<xsl:output method="html" indent="yes" />

<xsl:param name="sort" />
<xsl:param name="order" />

<xsl:param name="Page" select="0" />
<xsl:param name="PageSize" select="15" />

<xsl:param name="name" />
<xsl:param name="desig" />
<xsl:param name="admin" />

<xsl:template name="results" match="/">

	<!-- Pagination approach described by VivekAyer, 2010 on http://www.codeproject.com/Articles/11277/Pagination-using-XSL -->
	<xsl:variable name="mycount" select="count(features/feature)" />
	<xsl:variable name="selectedRowCount"
		select="floor(((number($mycount)-1) div $PageSize))+1" />

	<html>
	<body>
		<form METHOD="GET" ACTION="location.jsp">
	<table border="1" width="80%">
		<tr>
			<th>Origin</th>
			<th>Destination</th>
			<th>Full Name</th>
			<th>Designation</th>
			<th>Administrative Division</th>
			<th>Name Type</th>
			<th>Date Modified</th>
		</tr>
		<xsl:for-each select="features/feature">

			<!-- Sorting approach described by Dave Stratton, 2005 -->
			<xsl:sort select="(*|*/*)[name()=$sort]" order="{$order}" />
			<xsl:sort select="sort_key" order="{$order}" />
			<xsl:if test="position() &gt;= ($Page * $PageSize) + 1">
			<xsl:if test="position() &lt;= $PageSize + ($PageSize * $Page)">
		<tr>
							<td>
				<xsl:element name="input">
					<xsl:attribute name="type">radio</xsl:attribute>
					<xsl:attribute name="name">origin</xsl:attribute>
					<xsl:attribute name="value"><xsl:value-of
						select="@ufi" /></xsl:attribute>
				</xsl:element>
			</td>
			<td>
				<xsl:element name="input">
					<xsl:attribute name="type">radio</xsl:attribute>
					<xsl:attribute name="name">destination</xsl:attribute>
					<xsl:attribute name="value"><xsl:value-of
						select="@ufi" /></xsl:attribute>
				</xsl:element>
			</td>
			<td>
						<xsl:element name="a">
							<xsl:attribute name="href">
			<xsl:text>detail.jsp?ufi=</xsl:text>
			<xsl:value-of select="@ufi" />
			<xsl:text>&#38;des=</xsl:text>
			<xsl:value-of select="designation" />
			<xsl:text>&#38;adm=</xsl:text>
			<xsl:value-of select="administrative_division" />
			<xsl:text>&#38;type=</xsl:text>
			<xsl:value-of select="name_type" />
			<xsl:text>&#38;full=</xsl:text>
			<xsl:value-of select="full_name" />
			<xsl:text>&#38;sort=</xsl:text>
			<xsl:value-of select="sort_key" />
			<xsl:text>&#38;mod=</xsl:text>
			<xsl:value-of select="modified" />
		</xsl:attribute>
					<xsl:value-of select="full_name" />
				</xsl:element>
			</td>

			<td>
				<xsl:value-of select="designation" />
			</td>
			<td>
				<xsl:value-of select="administrative_division" />
			</td>
			<td>
				<xsl:value-of select="name_type" />
			</td>
			<td>
				<xsl:value-of select="modified" />
			</td>
		</tr>

			</xsl:if>
			</xsl:if>
		</xsl:for-each>
		<select name="units">
			<option>kilometres</option>
			<option>miles</option>
		</select>
		<input TYPE="SUBMIT" VALUE="Compare Selected"></input>
		</table>
		</form>
		</body>
	</html>

	<xsl:choose>
		<xsl:when test="number($Page)-1 &gt;= 0">
			&#160;
			<A>
		<xsl:attribute name="href">index.jsp?page=<xsl:value-of
			select="number($Page)-1" />&amp;pagesize=<xsl:value-of
			select="$PageSize" />&amp;name=<xsl:value-of select="$name" />&amp;designation=<xsl:value-of
			select="$desig" />&amp;administrative_division=<xsl:value-of
			select="$admin" />&amp;hide=1&amp;sort=<xsl:value-of
			select="$sort" />&amp;order=<xsl:value-of select="$order" /></xsl:attribute>
		&lt;&lt;Prev
			</A>
		</xsl:when>
		<xsl:otherwise>
			<!-- display something else -->
		</xsl:otherwise>
	</xsl:choose>
	<xsl:if test="$selectedRowCount &gt; 1">
		&#160;
		<b class="blacktext">
			<xsl:value-of select="number($Page)" />
			&#160;of&#160;
			<xsl:value-of select="number($selectedRowCount)" />
		</b>
		&#160;
	</xsl:if>

	<!-- Next link for pagination -->
	<xsl:choose>
		<xsl:when test="number($Page)+1 &lt; number($selectedRowCount)">
			&#160;
			<A>
		<xsl:attribute name="href">index.jsp?page=<xsl:value-of
			select="number($Page)+1" />&amp;pagesize=<xsl:value-of
			select="$PageSize" />&amp;name=<xsl:value-of select="$name" />&amp;designation=<xsl:value-of
			select="$desig" />&amp;administrative_division=<xsl:value-of
			select="$admin" />&amp;hide=1&amp;sort=<xsl:value-of
			select="$sort" />&amp;order=<xsl:value-of select="$order" /></xsl:attribute>
		Next&gt;&gt;
			</A>


		</xsl:when>
		<xsl:otherwise>
			<!-- display something else -->
		</xsl:otherwise>
	</xsl:choose>

	<form METHOD="GET" ACTION="index.jsp">
		<input type="hidden" name="hide" value="yes"></input>

		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">pagesize</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$PageSize" /></xsl:attribute>
		</xsl:element>
		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">designation</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$desig" /></xsl:attribute>
		</xsl:element>
		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">administrative_division</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$admin" /></xsl:attribute>
		</xsl:element>
		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">name</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$name" /></xsl:attribute>
		</xsl:element>
		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">sort</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$sort" /></xsl:attribute>
		</xsl:element>
		<xsl:element name="input">
			<xsl:attribute name="type">hidden</xsl:attribute>
			<xsl:attribute name="name">order</xsl:attribute>
			<xsl:attribute name="value"><xsl:value-of select="$order" /></xsl:attribute>
		</xsl:element>

		<input type="text" name="page" size="7"></input>

		<input TYPE="SUBMIT" VALUE="Go To Page"></input>

	</form>

</xsl:template>

<!-- Hide the following values -->
<xsl:template match="sort_key" />

</xsl:stylesheet>
