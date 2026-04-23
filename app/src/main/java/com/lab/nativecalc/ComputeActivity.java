package com.lab.nativecalc;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ComputeActivity extends AppCompatActivity {

    public native String computeGreeting();
    public native int computeFactorial(int inputVal);
    public native String invertText(String inputText);
    public native int totalizeArray(int[] inputData);

    static {
        System.loadLibrary("nativecalc-core");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layout_compute);

        TextView displayGreeting = findViewById(R.id.displayGreeting);
        TextView displayFactorial = findViewById(R.id.displayFactorial);
        TextView displayInverted = findViewById(R.id.displayInverted);
        TextView displayTotal = findViewById(R.id.displayTotal);

        displayGreeting.setText(computeGreeting());

        int factResult = computeFactorial(10);
        if (factResult >= 0) {
            displayFactorial.setText("Factoriel(10) = " + factResult);
        } else {
            displayFactorial.setText("Erreur factoriel, code retour = " + factResult);
        }

        String invertedOutput = invertText("Le NDK Android est utile !");
        displayInverted.setText("Texte inversé : " + invertedOutput);

        int[] sampleData = {15, 25, 35, 45, 55};
        int totalResult = totalizeArray(sampleData);
        displayTotal.setText("Somme du tableau = " + totalResult);
    }
}