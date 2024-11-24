/**
 * 
 */
/**
 * 
 */
module SAE {
	requires javafx.graphics;
    requires javafx.base;
    requires javafx.fxml;
    requires javafx.controls;
    requires java.desktop;

    opens controleur to javafx.graphics, javafx.fxml, javafx.base;
    opens modele to javafx.graphics, javafx.fxml, javafx.base;
    opens vue to javafx.graphics, javafx.fxml, javafx.base;
}