package com.sabanciuniv.repo;

import java.util.List;
import java.util.Optional;

import org.springframework.data.mongodb.repository.MongoRepository;

import com.sabanciuniv.model.Accounts;

public interface AccountsRepo extends MongoRepository < Accounts, String> { 

	public List<Accounts> findByid (String Id);
	//public List<Accounts> findAll (String Id);
	
}
