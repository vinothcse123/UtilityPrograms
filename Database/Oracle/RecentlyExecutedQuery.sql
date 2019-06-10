select sql_text, last_active_time     from v$sql v where lower(sql_text) like '%v6_over%' order by last_active_time desc
