<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
              xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
              xmlns:xhtml="http://www.w3.org/1999/xhtml"
              xmlns:v="http://verthandi.org/2014/verthandi"
              xmlns="http://www.w3.org/1999/xhtml"
              exclude-result-prefixes="xhtml v"
              version="1.0">
  <xsl:output method="xml" version="1.0" encoding="UTF-8"
              doctype-public="-//W3C//DTD XHTML 1.1//EN"
              doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
              indent="no"
              media-type="application/xhtml+xml" />

  <xsl:strip-space elements="*" />
  <xsl:preserve-space elements="xhtml:pre" />

  <xsl:template match="@*|node()">
    <xsl:copy>
      <xsl:apply-templates select="@*|node()" />
    </xsl:copy>
  </xsl:template>

  <xsl:template match="v:verthandi">
    <html>
      <head>
        <link rel="stylesheet" type="text/css" href="/css/verthandi"/>
      </head>
      <body>
        <xsl:apply-templates select="node()"/>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="v:project">
    <h1>
      <xsl:value-of select="@name"/>
    </h1>
    <xsl:choose>
      <xsl:when test="text()">
        <p><xsl:value-of select="text()"/></p>
      </xsl:when>
      <xsl:otherwise>
        <p>No description.</p>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>
</xsl:stylesheet>
