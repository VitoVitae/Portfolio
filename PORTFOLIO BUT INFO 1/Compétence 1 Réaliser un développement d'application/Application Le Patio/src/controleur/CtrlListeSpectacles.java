package controleur;

import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.*;
import javafx.fxml.FXML;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import modele.Donnees;
import modele.Spectacle;

public class CtrlListeSpectacles {

    @FXML
    private   TextField txt_numSpectateur = new TextField() ;
    @FXML
    private  TextField num_prixOrchestre = new TextField();
    @FXML
    private  TextField num_prixLogesDroites = new TextField();
    @FXML
    private  TextField txt_duree = new TextField();
    @FXML
    private  TextField num_prixLogesGauches = new TextField();
    @FXML
    private  TextField num_prixBalcon = new TextField();
    @FXML
    private  TextField txt_nomSpectacle = new TextField();
    @FXML
    private  TextField txt_genreSpectacle = new TextField();
    @FXML
    private  TextField txt_categorieSpectacle = new TextField();
    @FXML
    private  TableView<Spectacle> tvListeSpectacle = new TableView<Spectacle>();

    @FXML
    private  TableColumn<Spectacle, Number> txt_colonneDuree;
    @FXML
    private  TableColumn<Spectacle, Number> txt_colonneCapacite;
    @FXML
    private  TableColumn<Spectacle, String> txt_colonneGenre;
    @FXML
    private  TableColumn<Spectacle, String> txt_colonneCategorie;
    @FXML
    private  TableColumn<Spectacle, String> txt_colonneNom;

    @FXML
    void initialize() {
       
        txt_colonneNom.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getNom()));
        txt_colonneCategorie.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getCategorie().toString()));
        txt_colonneGenre.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getGenre()));
        txt_colonneCapacite.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getCapacite()));
        txt_colonneDuree.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().getDuree()));
        

        

        txt_nomSpectacle.textProperty().bind(
                Bindings.createStringBinding(() -> {
                	Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? spectSelected.getNom() : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        txt_genreSpectacle.textProperty().bind(
                Bindings.createStringBinding(() -> {
                	Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? spectSelected.getGenre() : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        txt_categorieSpectacle.textProperty().bind(
                Bindings.createStringBinding(() -> {
                	Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? spectSelected.getCategorie().toString() : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        num_prixOrchestre.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneOcherstre())) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        num_prixLogesDroites.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneDroite())) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        
        num_prixLogesGauches.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneGauche())) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        
        
        
        num_prixBalcon.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? Float.toString(spectSelected.tarifZone(Donnees.getTarifsZoneBalcon())) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        txt_duree.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ? Integer.toString(spectSelected.getDuree()) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        txt_numSpectateur.textProperty().bind(
                Bindings.createStringBinding(() -> {
                    Spectacle spectSelected = tvListeSpectacle.getSelectionModel().getSelectedItem();
                    return spectSelected != null ?Integer.toString( (spectSelected.getCapacite())) : "";
                }, tvListeSpectacle.getSelectionModel().selectedItemProperty())
        );
        tvListeSpectacle.setItems(Donnees.getLesSpectacle());
        tvListeSpectacle.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        
        
        
    }

}
