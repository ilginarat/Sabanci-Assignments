package com.sabanciuniv.model;

import java.time.LocalDateTime;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Accounts {

	@Id private String id;
	public String owner;
	public LocalDateTime createDate = LocalDateTime.now();
	
	
	public Accounts() {
		
	}
	
	
	public Accounts(String id, String owner) {
	
		this.id = id;
		this.owner = owner;

	}

	
	public Accounts( String owner) {
		
		this.owner = owner;
		this.createDate = LocalDateTime.now();
	}


	public String getId() {
		return id;
	}


	public void setId(String id) {
		this.id = id;
	}


	public String getOwner() {
		return owner;
	}


	public void setOwner(String owner) {
		this.owner = owner;
	}


	public LocalDateTime getCreateDate() {
		return createDate;
	}


	public void setCreateDate(LocalDateTime createDate) {
		this.createDate = createDate;
	}
	
	
	
}
