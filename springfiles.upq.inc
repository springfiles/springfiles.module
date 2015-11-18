<?php

//implementation of hook_cron
//rebuild internal file distribution server table from UPQ.
//rebuild internal mirrored files table from UPQ with md5 file hashes as our key.
function springfiles_cron() {
    db_set_active('upq');
    $q=db_query('SELECT * FROM mirror');
    db_set_active();
    db_query('truncate file_mirror');
    while ($obj = db_fetch_object($q))
    {
        db_query("INSERT INTO file_mirror (fmid, title, description, country, ftp_url, url_prefix, active) VALUES
                 ('%s', '%s', '%s', '%s', '%s', '%s', '%s')", array(
                                                  $obj->mid,
                                                  $obj->title,
                                                  $obj->description,
                                                  $obj->country,
                                                  $obj->ftp_url,
                                                  $obj->url_prefix,
                                                  $obj->status));
    }
    
    db_set_active('upq');
    $q=db_query('SELECT *, m.path FROM mirror_file m INNER JOIN file f on m.fid = f.fid');
    db_set_active();
    db_query('truncate file_mirror_files');
    while ($obj = db_fetch_object($q))
    {
        $x = db_query("SELECT fid FROM filehash WHERE md5 = '%s'", $obj->md5);
        $fid = db_fetch_object($x);
        if ($fid->fid != null)
        {
        db_query("INSERT INTO file_mirror_files (fmid, fid, path, size, md5, active, metadata) VALUES
                 ('%s', '%s', '%s', '%s', '%s', '%s', '%s')", array(
                                                  $obj->mid,
                                                  $fid->fid,
                                                  $obj->path,
                                                  $obj->size,
                                                  $obj->md5,
                                                  $obj->status,
                                                  $obj->metadata));
        }
    }
    
}