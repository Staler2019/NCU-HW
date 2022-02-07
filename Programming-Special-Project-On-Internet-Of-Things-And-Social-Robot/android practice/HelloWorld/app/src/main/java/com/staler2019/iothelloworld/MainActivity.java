package com.staler2019.iothelloworld;

import android.annotation.SuppressLint;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    EditText input_editText;
    Button sub_btn;
    Button cls_btn;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initViewElement();

        cls_btn.setOnClickListener((View view)->{
            input_editText.setText("");
        });

        sub_btn.setOnClickListener((View view) -> {
            Bundle bundle = new Bundle();
            bundle.putString("input", input_editText.getText().toString());

            Intent it = new Intent();
            it.putExtras(bundle);
            it.setClass(MainActivity.this, MainActivity2.class);
            startActivity(it);
        });

/* same as: due to this is a one function class
        sub_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Bundle bundle = new Bundle();
                bundle.putString("input", input_editText.getText().toString());

                Intent it = new Intent();
                it.putExtras(bundle);
                it.setClass(MainActivity.this, MainActivity2.class);
                startActivity(it);
            }
        });
*/
    }

    private void initViewElement() {
        // btn
        sub_btn = findViewById(R.id.sub_btn);
        cls_btn = findViewById(R.id.cls_btn);

        // editText
        input_editText = findViewById(R.id.input_editText); // class "EditText"
    }
}