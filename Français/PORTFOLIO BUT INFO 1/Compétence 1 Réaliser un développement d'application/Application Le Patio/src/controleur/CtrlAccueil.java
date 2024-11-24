package controleur;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class CtrlAccueil {

    @FXML
    void quitter(ActionEvent event) {
        Main.quitter();
    }
    
    @FXML
    void aPropos(ActionEvent event) {
        Main.afficherAPropos();
    }

}
