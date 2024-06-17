package modele;

import java.time.LocalDateTime;
import java.util.HashSet;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Donnees {
    static private ObservableList<Zone> lesZones = FXCollections.observableArrayList();
    static private ObservableList<CategorieSpectacle> lescategorieSpectacle = FXCollections.observableArrayList();
    static private ObservableList<CategorieSpectateur> lesCategorieSpectateur = FXCollections.observableArrayList();
    static private ObservableList<Artiste> lesArtiste = FXCollections.observableArrayList();
    private static ObservableList<Spectacle> lesSpectacle = FXCollections.observableArrayList();
    static private ObservableList<Representation> lesRepresentattion = FXCollections.observableArrayList();

    static {

//		lesZones =================================================================================================================
        lesZones.add(new Zone("balcon"));
        lesZones.add(new Zone("orchestre"));
        lesZones.add(new Zone("droite"));
        lesZones.add(new Zone("gauche"));

//		lescategorieSpectacle ====================================================================================================
        lescategorieSpectacle.add(CategorieSpectacle.A);
        lescategorieSpectacle.add(CategorieSpectacle.B);
        lescategorieSpectacle.add(CategorieSpectacle.C);

//		lesCategorieSpectateur ===================================================================================================
        lesCategorieSpectateur.add(new CategorieSpectateur("Jeune", "Personne de moins de 25 ans", .3));
        lesCategorieSpectateur.add(new CategorieSpectateur("Sénior", "Perosnne de plus de 65 ans", .25));
        lesCategorieSpectateur
                .add(new CategorieSpectateur("Abonné", "Personne qui assiste à au moins 3 spectacles par an", .3));
        lesCategorieSpectateur
                .add(new CategorieSpectateur("Groupe", "Personne membre d'un groupe d'au moins 20 adultes", .15));
        lesCategorieSpectateur
                .add(new CategorieSpectateur("Adulte", "Personne n'appartenant à aucune autre catégorie", 0d));

//		lesArtiste ===============================================================================================================
        lesArtiste.add(new Artiste("repar-auto"));
        lesArtiste.add(new Artiste("vito"));
        lesArtiste.add(new Artiste("scover"));
        lesArtiste.add(new Artiste("The great zetor's son Icelos"));
        lesArtiste.add(new Artiste("Sepultura"));
        lesArtiste.add(new Artiste("Roland Cristal"));

//		lesSpectacle =============================================================================================================
        lesSpectacle.add(new Spectacle("e", 120, 2_000, "chant grégorien", CategorieSpectacle.B));
        lesSpectacle.get(0).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(0).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(0).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(0).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);
        
        lesSpectacle.add(new Spectacle("Les empereurs du néant", 666, 666, "Metal gothique", CategorieSpectacle.A));
        lesSpectacle.get(1).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(1).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(1).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(1).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);
        
        lesSpectacle.add(new Spectacle("Les petits poisons dans l'eau", 20, 10000, "jazz", CategorieSpectacle.C));
        lesSpectacle.get(2).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(2).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(2).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(2).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);
        
        lesSpectacle.add(new Spectacle("Les petits cailloux", 3, 8_000_000, "révélation", CategorieSpectacle.A));
        lesSpectacle.get(3).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(3).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(3).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(3).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);
        
        lesSpectacle.add(new Spectacle("Moi lolita", 140, 20_400, "rap", CategorieSpectacle.A));
        lesSpectacle.get(4).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(4).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(4).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(4).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);
        
        lesSpectacle.add(new Spectacle("Roots", 3000, 50_000_000, "Groove Metal ", CategorieSpectacle.A));
        lesSpectacle.get(5).ajouterTarif(getTarifsZoneBalcon(), (float) 50.0);
        lesSpectacle.get(5).ajouterTarif(getTarifsZoneDroite(), (float) 50.0);
        lesSpectacle.get(5).ajouterTarif(getTarifsZoneGauche(), (float) 50.0);
        lesSpectacle.get(5).ajouterTarif(getTarifsZoneOcherstre(), (float) 50.0);

//		lesRepresentattion =======================================================================================================
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 6, 16, 8, 0), lesSpectacle.get(0)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 6, 23, 8, 0), lesSpectacle.get(0)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 6, 30, 8, 0), lesSpectacle.get(0)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 7, 14, 22, 30), lesSpectacle.get(1)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 6, 25, 05, 00), lesSpectacle.get(2)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2026, 1, 1, 00, 01), lesSpectacle.get(3)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 6, 12, 12, 30), lesSpectacle.get(4)));
        lesRepresentattion.add(new Representation(LocalDateTime.of(2024, 3, 27, 15, 15), lesSpectacle.get(5)));

    }

    static public void ajouterCategorie(CategorieSpectateur catSpect) {
        lesCategorieSpectateur.add(catSpect);
    }

    public static HashSet<String> getGenres() {
        return new HashSet<>(lesSpectacle.stream().map((s) -> s.getGenre()).toList());
    }

    public static ObservableList<Artiste> getLesArtiste() {
        return lesArtiste;
    }

    public static ObservableList<CategorieSpectacle> getLescategorieSpectacle() {
        return lescategorieSpectacle;
    }

    static public ObservableList<CategorieSpectateur> getlesCategorieSpectateur() {
        return lesCategorieSpectateur;
    }

    public static ObservableList<CategorieSpectateur> getLesCategorieSpectateur() {
        return lesCategorieSpectateur;
    }

    public static ObservableList<Representation> getLesRepresentattion() {
        return lesRepresentattion;
    }

    public static ObservableList<Spectacle> getLesSpectacle() {
        return lesSpectacle;
    }

    ///// Getters and setters
    public static ObservableList<Zone> getLesZones() {
        return lesZones;
    }

    public static Zone getTarifsZoneBalcon() {
        return lesZones.get(0);
    }

    public static Zone getTarifsZoneDroite() {
        return lesZones.get(2);
    }

    public static Zone getTarifsZoneGauche() {
        return lesZones.get(3);
    }

    public static Zone getTarifsZoneOcherstre() {
        return lesZones.get(1);
    }

    static public void modifierCategorie(CategorieSpectateur catSpect) {
        boolean trouve = false;
        int i = 0;
        while (!trouve && i < lesCategorieSpectateur.size()) {
            if (lesCategorieSpectateur.get(i).equals(catSpect)) {
                lesCategorieSpectateur.set(i, catSpect);
                trouve = true;
            }
            i++;
        }
    }

    static public void supprimerCategorie(CategorieSpectateur catSpect) {
        boolean trouve = false;
        int i = 0;
        while (!trouve && i < lesCategorieSpectateur.size()) {
            if (lesCategorieSpectateur.get(i).equals(catSpect)) {
                lesCategorieSpectateur.remove(i);
                trouve = true;
            }
            i++;
        }
    }

}
