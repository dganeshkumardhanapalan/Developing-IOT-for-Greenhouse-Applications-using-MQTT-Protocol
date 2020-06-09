package com.example.myapplication;
import java.util.ArrayList;

import java.util.Arrays;

import java.util.Date;

import java.util.HashMap;

import java.util.List;

import java.util.Map;

import java.util.concurrent.Callable;

import java.util.concurrent.Executor;

import java.util.concurrent.LinkedBlockingQueue;

import java.util.concurrent.ThreadPoolExecutor;

import java.util.concurrent.TimeUnit;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.content.Intent;
import com.google.firebase.Timestamp;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.Button;
import android.app.AlertDialog;
import android.content.DialogInterface;

import com.parse.Parse;
import com.parse.ParseException;
import com.parse.ParseUser;
import com.parse.SignUpCallback;
import com.google.firebase.firestore.CollectionReference;

import com.google.firebase.firestore.DocumentChange;

import com.google.firebase.firestore.DocumentChange.Type;

import com.google.firebase.firestore.DocumentReference;

import com.google.firebase.firestore.DocumentSnapshot;

import com.google.firebase.firestore.EventListener;

import com.google.firebase.firestore.FieldPath;

import com.google.firebase.firestore.FieldValue;

import com.google.firebase.firestore.FirebaseFirestore;

import com.google.firebase.firestore.FirebaseFirestoreException;

import com.google.firebase.firestore.FirebaseFirestoreSettings;

import com.google.firebase.firestore.ListenerRegistration;

import com.google.firebase.firestore.MetadataChanges;

import com.google.firebase.firestore.Query;

import com.google.firebase.firestore.Query.Direction;

import com.google.firebase.firestore.QueryDocumentSnapshot;

import com.google.firebase.firestore.QuerySnapshot;

import com.google.firebase.firestore.ServerTimestamp;

import com.google.firebase.firestore.SetOptions;

import com.google.firebase.firestore.Source;

import com.google.firebase.firestore.Transaction;

import com.google.firebase.firestore.WriteBatch;
public class SIGNUP extends AppCompatActivity {
EditText et,et2,et5,et6,et7,et8;
Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);
        et=(EditText)findViewById(R.id.editText );
        et2=(EditText)findViewById(R.id.editText2);
        et5=(EditText)findViewById(R.id.editText5);
        et6=(EditText)findViewById(R.id.editText6);
        et7=(EditText)findViewById(R.id.editText7);
        et8=(EditText)findViewById(R.id.editText8);
        btn=(Button)findViewById(R.id.button);

        final ProgressDialog dlg = new ProgressDialog(SIGNUP.this);
    btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Validating the log in data
                boolean validationError = false;
                      StringBuilder validationErrorMessage = new StringBuilder("Please, enter ");
                if (isEmpty(et)) {
                    validationError = true;
                    validationErrorMessage.append("a name");
                }
                    if (isEmpty(et7)) {
                        validationError = true;
                        validationErrorMessage.append("a mobile number");
                    }
                        if (isEmpty(et2)) {
                            validationError = true;
                            validationErrorMessage.append("a e-mail");
                        }
               if (isEmpty(et2)) {
                 validationError = true;
                    validationErrorMessage.append("an username");
                }
                if (isEmpty(et5)) {
                    if (validationError) {
                        validationErrorMessage.append(" and ");
                    }
                    validationError = true;
                    validationErrorMessage.append("a password");
                }
                if (isEmpty(et6)) {
                    if (validationError) {
                        validationErrorMessage.append(" and ");
                    }
                    validationError = true;
                    validationErrorMessage.append("your confirmation password ");
                }
                else {
                    if (!isMatching(et5,et6)) {
                        if (validationError) {
                            validationErrorMessage.append(" and ");
                        }
                        validationError = true;
                        validationErrorMessage.append("the same password twice.");
                    }
                }
                validationErrorMessage.append(".");

                if (validationError) {
                    Toast.makeText(SIGNUP.this, validationErrorMessage.toString(), Toast.LENGTH_LONG).show();
                    return;
                }
                //Setting up a progress dialog
                final ProgressDialog dlg = new ProgressDialog(SIGNUP.this);
                dlg.setTitle("Please, wait a moment.");
                dlg.setMessage("Signing up...");
                dlg.show();

                ParseUser user = new ParseUser();
                user.setUsername(et.getText().toString());
                user.setUsername(et7.getText().toString());
                user.setUsername(et8.getText().toString());
                user.setUsername(et2.getText().toString());
                user.setPassword(et5.getText().toString());
                user.signUpInBackground(new SignUpCallback() {
                    @Override
                    public void done(ParseException e) {
                        if (e == null) {
                            dlg.dismiss();
                            alertDisplayer("Sucessful Login","Welcome " + et.getText().toString() + "!");

                        } else {
                            dlg.dismiss();
                            ParseUser.logOut();
                            Toast.makeText(SIGNUP.this, e.getMessage(), Toast.LENGTH_LONG).show();
                        }
                    }
                });

            }
    });
    }

    private boolean isEmpty(EditText text) {
        if (text.getText().toString().trim().length() > 0) {
            return false;
        } else {
            return true;
        }
    }

    private boolean isMatching(EditText text1, EditText text2){
        if(text1.getText().toString().equals(text2.getText().toString())){
            return true;
        }
        else{
            return false;
        }
    }

    private void alertDisplayer(String title,String message){
        AlertDialog.Builder builder = new AlertDialog.Builder(SIGNUP.this)
                .setTitle(title)
                .setMessage(message)
                .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.cancel();
                        Intent intent = new Intent(SIGNUP.this, App.class);
                        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK | Intent.FLAG_ACTIVITY_NEW_TASK);
                        startActivity(intent);
                    }
                });
        AlertDialog ok = builder.create();
        ok.show();
    }
}