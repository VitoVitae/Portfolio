package controleur;

import javafx.fxml.FXML;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import modele.Donnees;
import modele.Spectacle;

public class CtrlAfficheSpectacle {

    @FXML
    private TextField txt_numSpectateur;
    @FXML
    private TextField num_prixOrchestre;
    @FXML
    private TextField num_prixLogesDroites;
    @FXML
    private TextField txt_duree;
    @FXML
    private TextField num_prixLogesGauches;
    @FXML
    private TextField num_prixBalcon;
    @FXML
    private TextField txt_nomSpectacle;
    @FXML
    private TextField txt_genreSpectacle;
    @FXML
    private TextField txt_categorieSpectacle;
    @FXML
    private TableView<Spectacle> tvListeSpectacle;

    @FXML
    private TableColumn<Spectacle, Integer> txt_colonneDuree;
    @FXML
    private TableColumn<Spectacle, Integer> txt_colonneCapacite;
    @FXML
    private TableColumn<Spectacle, String> txt_colonneGenre;
    @FXML
    private TableColumn<Spectacle, String> txt_colonneCategorie;
    @FXML
    private TableColumn<Spectacle, String> txt_colonneNom;

    public Spectacle spectSelected;

//    Person person = taview.getSelectionModel().getSelectedItem();
    public void actualiser() {
        spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
        txt_numSpectateur.setText(Integer.toString(spectSelected.getCapacite()));
        num_prixOrchestre.setText(Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneDroite())));
        num_prixLogesDroites.setText(Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneOcherstre())));
        txt_duree.setText(Integer.toString(spectSelected.getDuree()));
        num_prixLogesGauches.setText(Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneGauche())));
        num_prixBalcon.setText(Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneBalcon())));
        txt_nomSpectacle.setText(spectSelected.getNom());
        txt_genreSpectacle.setText(spectSelected.getGenre());
        txt_categorieSpectacle.setText(spectSelected.getCategorie().toString());

    }

    @FXML
    void initialize() {
        TableColumn<Spectacle, String> colonne1 = new TableColumn<>("Nom");
        colonne1.setCellValueFactory(new PropertyValueFactory<>("nom"));
        tvListeSpectacle.getColumns().set(0, colonne1);

        TableColumn<Spectacle, String> colonne2 = new TableColumn<>("Categorie");
        colonne2.setCellValueFactory(new PropertyValueFactory<>("categorie"));
        tvListeSpectacle.getColumns().set(1, colonne2);
        TableColumn<Spectacle, Integer> colonne3 = new TableColumn<>("Capacite");
        colonne3.setCellValueFactory(new PropertyValueFactory<>("capacite"));
        tvListeSpectacle.getColumns().set(2, colonne3);
        TableColumn<Spectacle, Integer> colonne4 = new TableColumn<>("Duree");
        colonne4.setCellValueFactory(new PropertyValueFactory<>("duree"));
        tvListeSpectacle.getColumns().set(3, colonne4);
        TableColumn<Spectacle, String> colonne5 = new TableColumn<>("Genre");
        colonne5.setCellValueFactory(new PropertyValueFactory<>("genre"));
        tvListeSpectacle.getColumns().set(4, colonne5);

        tvListeSpectacle.setItems(Donnees.getLesSpectacle());
        tvListeSpectacle.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        // griser les boutons Modifier et Supprimer quand aucune s�lection

    }

}
