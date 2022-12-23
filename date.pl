#!C:/perl/bin/perl.exe
use warnings;
use strict;
use CGI;
use CGI::Carp 'fatalsToBrowser';
use File::Spec;
use PHP::Session;
use POSIX qw(strftime);

# Date et heure
my $date = strftime "%d/%m/%Y %H:%M:%S", localtime;

# Nom de la session et répertoire où sont stockés les fichiers de session.
my $nom_session        = 'SessionPHP';
my $repertoire_session = 'C:\TEMP';

my $cgi = new CGI;

# Cookie
my $cookie = $cgi->cookie( -name => $nom_session );
my $fichier_session = File::Spec->catfile( $repertoire_session, 'sess_' . $cookie );

# Vérifions l'existence de la session et du cookie
if ( ( not defined $cookie ) or ( !-e $fichier_session ) ) {
  redirection($cgi);
}

# Lecture ou création de la session
my $session = PHP::Session->new(
  $cookie,
  { save_path => $repertoire_session,
    auto_save => 1,            # Sauvegarde de la session en cas de modification
    create    => 1,
  }
);

# Variable de session identifiant
my $identifiant = $session->get('identifiant');
if ( not defined $identifiant or $identifiant ne 'test' ) {
  redirection($cgi);
}

print $cgi->header( -charset => 'utf-8', );
print $cgi->start_html(
  -title => 'Perl - Etape 2 : date',
  -style => { 'src' => '/sessions/style.css' },
);

my $id = $session->id;
$session->set( date => $date );

print '<h1 class="center">Perl - &Eacute;tape 2 </h1>';
print '<div class="deconnexion"><a href="/sessions/deconnexion.php">Se d&eacute;connecter</a></div>';

print <<"RESUME";
Bonjour <b>$identifiant</b>, aujourd'hui, nous sommes le : $date<br><br>
Cookie : <b>$cookie</b><br>
Id session : <b>$id</b><br><br>
Perl, affiche ma version : <a href="/cgi-bin/version-perl.pl">ici</a>
RESUME

print $cgi->end_html;

sub redirection {
  my $cgi = shift;
  print $cgi->header(
    -charset => 'utf-8',
    -Refresh => '4; URL=http://localhost/sessions/index.php',
  );
  print $cgi->start_html(
    -title => "Perl - Etape 2 : interdiction",
    -style => { 'src' => '/sessions/style.css' },
  );
  print "<p class='erreur center'>La session <b>$nom_session</b> est inconnue ou 
  vous n'avez pas le droit de lire cette page.</p>";
  print "<p class='center'>Redirection dans quatre secondes.</p>";
  print $cgi->end_html;
  exit;
}
