package com.staler2019.iothelloworld;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity2 extends AppCompatActivity {

    TextView msg_lbl;
    Button ret_btn;

    @Override
    protected void onCreate(Bundle savedInstStat) {
        super.onCreate(savedInstStat);
        setContentView(R.layout.activity_main2);

        initViewElement();

        Intent it = this.getIntent();
        if (it != null) {
            Bundle bundle = it.getExtras();
            if (bundle != null) {
                String inpStr = bundle.getString("input");
                if (inpStr != null && !inpStr.equals("")) {
                    msg_lbl.setText(inpStr);
                }
            }
        }

        ret_btn.setOnClickListener((View view) -> finish());
/*  same as: due to this is a one function class
        ret_btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){ finish(); }
        });
*/
    }


    private void initViewElement() {
        ret_btn = findViewById(R.id.ret_btn); // class "Button"
        msg_lbl = findViewById(R.id.msg_lbl); // class "EditText"
    }
}
