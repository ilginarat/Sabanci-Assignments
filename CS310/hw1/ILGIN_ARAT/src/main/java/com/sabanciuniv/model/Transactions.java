package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Transactions {
	
	@Id private String id;
	//@DBRef (db = "Accounts", field = "id")
	public String fromAcc;
	//@DBRef
	public String toAcc;
	public double amount;
	
	
	public Transactions() {

	}
	
	
	public Transactions(String fromAcc, String toAcc, double amount) {
	
		this.fromAcc = fromAcc;
		this.toAcc = toAcc;
		this.amount = amount;
	}


	public String getFromAcc() {
		return fromAcc;
	}


	public void setFromAcc(String fromAcc) {
		this.fromAcc = fromAcc;
	}


	public String getToAcc() {
		return toAcc;
	}


	public void setToAcc(String toAcc) {
		this.toAcc = toAcc;
	}


	public double getAmount() {
		return amount;
	}


	public void setAmount(double amount) {
		this.amount = amount;
	}
	
	
	
}
