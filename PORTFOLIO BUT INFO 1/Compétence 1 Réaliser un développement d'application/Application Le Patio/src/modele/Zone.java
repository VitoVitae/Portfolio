package modele;

import java.util.HashMap;

public final class Zone {
    private String nom;

    private HashMap<Spectacle, Float> tarifs;

    public Zone(String n) {
        nom = n;
        tarifs = new HashMap<>();
    }

    // Tarifs
    public void ajouterTarif(Spectacle s, Float f) throws IllegalArgumentException {
        if (!tarifs.containsKey(s) && (s != null)) {
            putTarif(s, f);
            s.putTarif(this, f);
        } else {
            if (s == null) {
                throw new IllegalArgumentException("Spectacle en entrée est null");
            } else {
                throw new IllegalArgumentException("Spectacle est déja dans le HashMap");
            }
        }
    }

    // Getterss et setters
    public String getNom() {
        return nom;
    }

    public HashMap<Spectacle, Float> getTarifs() {
        return tarifs;
    }

    // pour utilisation externe (liaison bi-directionelle)
    public void putTarif(Spectacle s, Float f) {
        tarifs.put(s, f);
    }

    public void removeTarif(Spectacle s) {
        tarifs.remove(s);
    }

    public void retirerTarif(Spectacle s) throws IllegalArgumentException {
        if (tarifs.containsKey(s) && (s != null)) {
            removeTarif(s);
            s.removeTarif(this);
        } else {
            if (s == null) {
                throw new IllegalArgumentException("Spectacle en entrée est null");
            } else {
                throw new IllegalArgumentException("Spectacle n'est pas dans le HashMap");
            }
        }
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public void setTarifs(HashMap<Spectacle, Float> tarifs) {
        this.tarifs = tarifs;
    }

    public float tarifSpectacle(Spectacle s) {
        return tarifs.get(s);
    }

    @Override
    public String toString() {
        return nom;
    }
}
