
<?php
/**
*This file
*<ul>
*<li>Implements security feature - which albums are authorized for view</li>
*<li>Creates albums</li>
*<li>Displays and sorts albums</li>
*</ul>
*
*<b>Note :</b> $cameralife and $topic are set by ShowPage()
  *@author Will Entriken <cameralife@phor.net>
  *@copyright Copyright (c) 2001-2009 Will Entriken
  *@access public
  */
  /**
  */
  # $cameralife and $topic are set by ShowPage()

  $cameralife->GetFeature('security');
  $cameralife->GetFeature('photostore');

  $albums = $topic->GetAlbums();
  $counts = $topic->GetCounts();

  $cameralife->Theme->Header($cameralife->GetPref('sitename').' : '.htmlentities($topic->GetName()), 'topic');
?>
<div id="text">
<form name="form1" method=post action="album_controller.php">
<?php
  $menu = array();
  $menu[] = $cameralife->GetIcon('small');
  if ($cameralife->Security->authorize('admin_albums'))
  {
    $menu[] = array('name'=>"Add an album to \"".htmlentities($topic->GetName())."\"",
                    'href'=>"search.php&#63;albumhelp=1",
                    'image'=>'small-album');
  }
  $menu[] = array('name'=>"Search for \"".htmlentities($topic->GetName())."\"",
                  'href'=>'search.php&#63;q='.urlencode($topic->GetName()),
                  'image'=>'small-search');

#  $cameralife->Theme->TitleBar('Photo albums of '.$_GET['name'],
#                               'topic',
#                               "(".$counts['albums']." albums)",
#                               $menu);

  if ($_GET['edit'])
  {
    $cameralife->Security->authorize('admin_albums',1);
?>
  <div class="administrative" align=center>
    <input type="hidden" name="param4" value="<?= htmlentities($_GET['term']) ?>">
    <input type="hidden" name="target" value="<?= $cameralife->base_url ?>/index.php">

    <p class="info" align=left>
      You are about to create an Album of photos whose descriptions contain "<b><?= htmlentities($_GET['term']) ?></b>".
      <a href="http://fdcl.sourceforge.net/wiki/index.php/Albums">Click here for more information about albums</a>
    </p>
    <table>
      <tr>
        <td>The Album's name:
        <td><input type="text" name="param3" value="<?= htmlentities(ucwords($_GET['term'])) ?>">
      <tr>
        <td>This album and others like it are:
        <td><select name="param1">
          <?php 
            foreach (Topic::GetTopics() as $thetopic)
            {
                $selected = ($album['topic'] == $thetopic) ? 'selected' : '';
                if ($album['topic'] == $thetopic) $preselect = true;
                echo "<option $selected onclick=\"javascript:document.form1.topicother.disabled=true\" value=\"$thetopic\">$thetopic</option>\n";
            }
          ?>
            <option value="othertopic" <?= $preselect ? '' : 'selected' ?> onclick="javascript:document.form1.topicother.disabled=false">(A new topic)</option>
          </select>
          <input <?= $preselect ? 'disabled' : '' ?> type="text" name="param2" name="topicother" id="topicother" value="NEW TOPIC">
      <tr>
        <td>
        <td>
          <input type=submit name="action" value="Create">
          <a href="search.php&#63;q=<?= urlencode($topic->GetName()) ?>">(cancel)</a>
    </table>
  </div>
<?php
    exit();
  }

  $cameralife->Theme->Grid($albums);
  
  if ($sort == 'rand()') $start = -1;
  $cameralife->Theme->PageSelector($start,$total,12,"name=".urlencode($_GET["name"]));
?>
</form>

<form method="POST" action="">
<p>
  Sort by <select name="sort">
<?php
    $options = $topic->SortOptions();
    foreach($options as $option)
      echo "    <option ".$option[2]." value=\"".$option[0]."\">".$option[1]."</option>\n";
?>
  </select>
  <input type=submit value="Sort">
</p>
</form>
<?php
  $cameralife->Theme->Footer();
?>











