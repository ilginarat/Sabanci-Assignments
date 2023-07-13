package com.sabanciuniv.repo;

import java.util.List;
import java.util.Optional;

import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.mongodb.repository.Query;

import com.sabanciuniv.model.Transactions;

public interface TransactionsRepo extends MongoRepository < Transactions, String> {

	public List<Transactions> findByid (String id);
	public List<Transactions>  findByfromAcc (String id);
	public List<Transactions>  findBytoAcc (String id);
	
	@Query("{fromAcc: '?0'}")
	public List<Transactions> findOut(String fromAcc);
	
	@Query("{toAcc: '?0'}")
	public List<Transactions> findIn(String toAcc);

	
}