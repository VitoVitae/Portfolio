package controleur;

import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SeparatorMenuItem;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import java.text.NumberFormat;
import modele.CategorieSpectateur;
import modele.Donnees;

public class CtrlListeCategories {

    static private final ObservableList<CategorieSpectateur> lstCategorie = FXCollections.observableArrayList();

    static private final NumberFormat percentageFormat = NumberFormat.getPercentInstance();
    static {
        percentageFormat.setMinimumFractionDigits(2);
    }
    
    @FXML
    private Button btnSupprimerCategorie;

    @FXML
    private Button btnModifieCategorie;

    @FXML
    private Button btnAjoutCategorie;

    @FXML
    private TableView<CategorieSpectateur> tvListeCategorie;

    @FXML
    private TableColumn<CategorieSpectateur, String> tabColNom;

    @FXML
    private TableColumn<CategorieSpectateur, String> tabColDescription;

    @FXML
    private TableColumn<CategorieSpectateur, String> tabColTaux;

    private final MenuItem optionAjouter = new MenuItem("Ajouter...");
    private final MenuItem optionModifier = new MenuItem("Modifier...");
    private final MenuItem optionSupprimer = new MenuItem("Supprimer");

    private final ContextMenu menu = new ContextMenu(optionAjouter, new SeparatorMenuItem(), optionModifier,
            new SeparatorMenuItem(), optionSupprimer);

    @FXML
    public void ajouterCategorie(ActionEvent event) {
        var nouvelleCat = Main.afficherCreationCategorie(null);
        if (nouvelleCat != null) {
            lstCategorie.add(nouvelleCat);
        }
    }

    @FXML
    public void initialize() {
        lstCategorie.addAll(Donnees.getlesCategorieSpectateur());

        tabColNom.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getNom()));
        tabColDescription.setCellValueFactory(p -> new SimpleStringProperty(p.getValue().getDescription()));
        tabColTaux.setCellValueFactory(p -> new SimpleStringProperty(percentageFormat.format(p.getValue().getReduction())));
        tvListeCategorie.setItems(lstCategorie);

        BooleanBinding rien = Bindings.equal(tvListeCategorie.getSelectionModel().selectedIndexProperty(), -1);
        btnModifieCategorie.disableProperty().bind(rien);
        btnSupprimerCategorie.disableProperty().bind(rien);
        optionModifier.disableProperty().bind(rien);
        optionSupprimer.disableProperty().bind(rien);

        tvListeCategorie.setContextMenu(menu);
        optionAjouter.setOnAction(this::ajouterCategorie);
        optionModifier.setOnAction(this::modifierCategorie);
        optionSupprimer.setOnAction(this::supprimerCategorie);
    }

    @FXML
    public void modifierCategorie(ActionEvent event) {
        int i = tvListeCategorie.getSelectionModel().getSelectedIndex();
        lstCategorie.set(i, Main.afficherCreationCategorie(lstCategorie.get(i)));
    }

    @FXML
    public void supprimerCategorie(ActionEvent event) {
        Alert alert = new Alert(AlertType.CONFIRMATION, "Voulez-vous vraiment supprimer cette catégorie ?",
                ButtonType.YES, ButtonType.NO);
        alert.setTitle("Confirmation de suppression");
        alert.showAndWait();
        if (alert.getResult() == ButtonType.YES) {
            Main.supprimerCategorie(tvListeCategorie.getSelectionModel().getSelectedItem());
            lstCategorie.remove(tvListeCategorie.getSelectionModel().getSelectedItem());
        }
    }
}
