<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US" lang="en-US">
<!-- git web interface version 1.7.0.9.GIT, (C) 2005-2006, Kay Sievers <kay.sievers@vrfy.org>, Christian Gierke -->
<!-- git core binaries version 1.7.0.9.GIT -->
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8"/>
<meta name="generator" content="gitweb/1.7.0.9.GIT git/1.7.0.9.GIT"/>
<meta name="robots" content="index, nofollow"/>
<title>Public Git Hosting - pluto.git/blob - examples/corcol/util.h</title>
<script type="text/javascript">/* <![CDATA[ */
function fixBlameLinks() {
	var allLinks = document.getElementsByTagName("a");
	for (var i = 0; i < allLinks.length; i++) {
		var link = allLinks.item(i);
		if (link.className == 'blamelink')
			link.href = link.href.replace("/blame/", "/blame_incremental/");
	}
}
/* ]]> */</script>
<base href="http://repo.or.cz/w" />
<link rel="stylesheet" type="text/css" href="/gitweb.css"/>
<link rel="alternate" title="pluto.git - history of examples/corcol/util.h - RSS feed" href="/w/pluto.git/rss?f=examples/corcol/util.h" type="application/rss+xml" />
<link rel="alternate" title="pluto.git - history of examples/corcol/util.h - RSS feed (no merges)" href="/w/pluto.git/rss?f=examples/corcol/util.h;opt=--no-merges" type="application/rss+xml" />
<link rel="alternate" title="pluto.git - history of examples/corcol/util.h - Atom feed" href="/w/pluto.git/atom?f=examples/corcol/util.h;opt=--no-merges" type="application/atom+xml" />
<link rel="alternate" title="pluto.git - history of examples/corcol/util.h - Atom feed (no merges)" href="/w/pluto.git/atom?f=examples/corcol/util.h;opt=--no-merges" type="application/atom+xml" />
<link rel="shortcut icon" href="/git-favicon.png" type="image/png" />
<script src="/gitweb.js" type="text/javascript"></script>
</head>
<body>
<div class="page_header">
<a title="git homepage" href="http://git-scm.com/"><img src="/git-logo.png" width="72" height="27" alt="git" class="logo"/></a><a href="/w">repo.or.cz</a> / <a href="/w/pluto.git">pluto.git</a> / blob
</div>
<form method="get" action="/w/pluto.git" enctype="application/x-www-form-urlencoded">
<div class="search">
<input name="a" type="hidden" value="search" />
<input name="h" type="hidden" value="HEAD" />
<select name="st" >
<option selected="selected" value="commit">commit</option>
<option value="grep">grep</option>
<option value="author">author</option>
<option value="committer">committer</option>
<option value="pickaxe">pickaxe</option>
</select><sup><a href="/w/pluto.git/search_help">?</a></sup> search:
<input type="text" name="s"  />
<span title="Extended regular expression"><label><input type="checkbox" name="sr" value="1" />re</label></span></div>
</form>
<div class="page_nav">
<a href="/w/pluto.git">summary</a> | <a href="/w/pluto.git/shortlog">log</a> | <a href="/git-browser/by-commit.html?r=pluto.git">graphiclog</a> | <a href="/w/pluto.git/commit/HEAD">commit</a> | <a href="/w/pluto.git/commitdiff/HEAD">commitdiff</a> | <a href="/w/pluto.git/tree/HEAD">tree</a> | <a href="/w/pluto.git/refs">refs</a> | <a href="/editproj.cgi?name=pluto.git">edit</a> | <a href="/regproj.cgi?fork=pluto.git">fork</a><br/>
<a href="/w/pluto.git/blame/HEAD:/examples/corcol/util.h">blame</a> | <a href="/w/pluto.git/history/HEAD:/examples/corcol/util.h">history</a> | <a href="/w/pluto.git/blob_plain/HEAD:/examples/corcol/util.h">raw</a> | <a href="/w/pluto.git/blob/HEAD:/examples/corcol/util.h">HEAD</a><br/>
</div>
<div class="header">
<span class="title"><a class="title" href="/w/pluto.git/commit/HEAD">update examples to print output to stderr and timing info to stdout</a><a class="cover" href="/w/pluto.git/commit/HEAD"></a></span>
</div>
<div class="page_path"><a title="tree root" href="/w/pluto.git/tree/HEAD">[pluto.git]</a> / <a title="examples" href="/w/pluto.git/tree/HEAD:/examples">examples</a> / <a title="examples/corcol" href="/w/pluto.git/tree/HEAD:/examples/corcol">corcol</a> / <a title="examples/corcol/util.h" href="/w/pluto.git/blob_plain/HEAD:/examples/corcol/util.h">util.h</a><br/></div>
<div class="page_body">
</div><div class="page_footer">
<div class="page_footer_text">Pluto - polyhedral automatic parallelizer</div>
<a class="rss_logo" title="history of examples/corcol/util.h RSS feed" href="/w/pluto.git/rss?f=examples/corcol/util.h">RSS</a>
<a class="rss_logo" title="history of examples/corcol/util.h Atom feed" href="/w/pluto.git/atom?f=examples/corcol/util.h">Atom</a>
</div>
</body>
</html>