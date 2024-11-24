package vue;

import java.io.IOException;

import controleur.CtrlAccueil;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class FenAPropos extends Stage {
   

    public FenAPropos() throws IOException {
        this.setTitle("À propos");
        this.setResizable(false);
        Scene scene = new Scene(creerSceneGraph());
        this.setScene(scene);
    }

    private Pane creerSceneGraph() throws IOException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/aPropos.fxml"));
        Pane root = loader.load();
        return root;
    }
}
