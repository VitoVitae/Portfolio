package modele;

import javafx.collections.ObservableList;

public class Test{
    public static void main(String[] args) {
    	// données pour test
    	ObservableList<Artiste> lesArtiste = Donnees.getLesArtiste();
    	ObservableList<Representation> lesRepresentattion = Donnees.getLesRepresentattion();
    	ObservableList<Spectacle> lesSpectacle = Donnees.getLesSpectacle();
    	ObservableList<Zone> lesZones = Donnees.getLesZones();
    	
    	
    	//////////Test Artiste
	 	System.out.println("Test Artiste");
	 	// ajouterSpectacle
	 	System.out.println("ajouterSpectacle");
	 	try {
				Artiste a1 = lesArtiste.get(0);
				a1.ajouterSpectacle(null);
		} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
		}
	 	
	 	try {
	 			Artiste a1 = lesArtiste.get(0);
				a1.ajouterSpectacle(lesSpectacle.get(0));
				a1.ajouterSpectacle(lesSpectacle.get(0));
		} catch (Exception e) {
				// doit donner erreur spectacle déja dans liste
				System.out.println(e);
		}
	 	System.out.println();
	 	
	 	// retirerSpectacle
	 	System.out.println("retirerSpectacle");
	 	try {
			Artiste a1 = lesArtiste.get(0);
			a1.retirerSpectacle(null);
		} catch (Exception e) {
			// doit donner null erreur
			System.out.println(e);
		}
 	
	 	try {
 			Artiste a1 = lesArtiste.get(0);
			a1.retirerSpectacle(lesSpectacle.get(0));
			a1.retirerSpectacle(lesSpectacle.get(0));
		} catch (Exception e) {
			// doit donner erreur pas dans liste
			System.out.println(e);
		}
	 	System.out.println();
    	
	 	
	 	//////////Test Representation
	 	System.out.println("Test Representation");
	 	// ajouterRepresente
	 	System.out.println("ajouterRepresente");
	 	try {
				Representation r1 = lesRepresentattion.get(0);
				r1.ajouterRepresente(null);
		} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
		}
	 	
	 	System.out.println();
	 	
	 	// retirerRepresente
	 	System.out.println("retirerRepresente");
	 	try {
	 		Representation r1 = lesRepresentattion.get(0);
	 		r1.retirerRepresente(null);
		} catch (Exception e) {
			// doit donner erreure entrée incorrect, car entrée n'est pas égal au spectacle
			System.out.println(e);
		}
	
	 	System.out.println();
	 	
	 	//////////Test Spectacle
	 	System.out.println("Test Spectacle");
	 	// ajouterArtiste
	 	System.out.println("ajouterArtiste");
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterArtiste(null);
		} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
		}
	 	
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterArtiste(lesArtiste.get(0));
	 			s1.ajouterArtiste(lesArtiste.get(0));
		} catch (Exception e) {
				// doit donner erreur artiste déja dans liste
				System.out.println(e);
		}
	 	System.out.println();
	 	
	 	// retirerArtiste
	 	System.out.println("retirerArtiste");
	 	try {
	 		Spectacle s1 = lesSpectacle.get(0);
 			s1.retirerArtiste(null);
		} catch (Exception e) {
			// doit donner null erreur
			System.out.println(e);
		}
	
	 	try {
 			Spectacle s1 = lesSpectacle.get(0);
 			s1.retirerArtiste(lesArtiste.get(0));
 			s1.retirerArtiste(lesArtiste.get(0));
		} catch (Exception e) {
			// doit donner erreur pas dans liste
			System.out.println(e);
		}
	 	System.out.println();
	 	
	 	// ajouterRepresentation
	 	System.out.println("ajouterRepresentation");
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterRepresentation(null);
		} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
		}
	 	
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterRepresentation(lesRepresentattion.get(0));
	 			s1.ajouterRepresentation(lesRepresentattion.get(0));
		} catch (Exception e) {
				// doit donner erreur représentation déja dans liste
				System.out.println(e);
		}
	 	System.out.println();
	 	
	 	// retirerRepresentation
	 	System.out.println("retirerRepresentation");
	 	try {
	 		Spectacle s1 = lesSpectacle.get(0);
			s1.retirerRepresentation(null);
		} catch (Exception e) {
			// doit donner null erreur
			System.out.println(e);
		}
	
	 	try {
			Spectacle s1 = lesSpectacle.get(0);
			s1.retirerRepresentation(lesRepresentattion.get(0));
			s1.retirerRepresentation(lesRepresentattion.get(0));
		} catch (Exception e) {
			// doit donner erreur pas dans liste
			System.out.println(e);
		}
	 	System.out.println();
	 	
	 	// ajouterTarif
	 	System.out.println("ajouterTarif");
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterTarif(null, 0.1f);
			} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
			}
	 	
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.ajouterTarif(lesZones.get(0), 0.1f);
	 			s1.ajouterTarif(lesZones.get(0), 0.1f);
			} catch (Exception e) {
				// doit donner erreur Zone déja dans hashmap
				System.out.println(e);
			}
	 	System.out.println();
	 	
	 	// retirerTarif
	 	System.out.println("retirerTarif");
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.retirerTarif(null);
			} catch (Exception e) {
				// doit donner null erreur
				System.out.println(e);
			}
	 	
	 	try {
	 			Spectacle s1 = lesSpectacle.get(0);
	 			s1.retirerTarif(lesZones.get(0));
				s1.retirerTarif(lesZones.get(0));
			} catch (Exception e) {
				// doit donner erreur pas dans hashmap
				System.out.println(e);
			}
	 	System.out.println();
	 	
	 	

    	////////// Test Zones
    	System.out.println("Test Zones");
    	// ajouterTarif
    	System.out.println("ajouterTarif");
    	try {
			Zone z1 = lesZones.get(0);
			z1.ajouterTarif(null, 0.1f);
		} catch (Exception e) {
			// doit donner null erreur
			System.out.println(e);
		}
    	
    	try {
			Zone z1 = lesZones.get(0);
			z1.ajouterTarif(lesSpectacle.get(0), 0.1f);
			z1.ajouterTarif(lesSpectacle.get(0), 0.1f);
		} catch (Exception e) {
			// doit donner erreur spectacle déja dans hashmap
			System.out.println(e);
		}
    	System.out.println();
    	
    	// retirerTarif
    	System.out.println("retirerTarif");
    	try {
			Zone z1 = lesZones.get(0);
			z1.retirerTarif(null);
		} catch (Exception e) {
			// doit donner null erreur
			System.out.println(e);
		}
    	
    	try {
			Zone z1 = lesZones.get(0);
			z1.retirerTarif(lesSpectacle.get(0));
			z1.retirerTarif(lesSpectacle.get(0));
		} catch (Exception e) {
			// doit donner erreur pas dans hashmap
			System.out.println(e);
		}
    	System.out.println();
    	
    }
}