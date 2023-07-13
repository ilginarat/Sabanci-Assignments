package com.sabanciuniv.controller;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


import javax.annotation.PostConstruct;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.annotation.Id;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
//import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.sabanciuniv.model.Accounts;
import com.sabanciuniv.model.Transactions;
import com.sabanciuniv.repo.AccountsRepo;
import com.sabanciuniv.repo.TransactionsRepo;


@RestController
public class bankRestController {

	@Autowired private AccountsRepo accRepo;	
	@Autowired private TransactionsRepo transRepo;
	
	
	private static final Logger logger= LoggerFactory.getLogger(bankRestController.class); 
	
	@PostConstruct
	public void init () {
		
		if (transRepo.count() == 0 && accRepo.count()== 0) {
			
			
			Accounts acc1 = new Accounts("1111", "Ali");
			Accounts acc2 = new Accounts("2222", "Veli");
			
			accRepo.save(acc1);
			accRepo.save(acc2);
			
			//Accounts a = accRepo.findByid("2222").get(0);
			//logger.info(a.owner);
			
			
			Transactions t1 = new Transactions("1111", "2222", 1500.0);
			Transactions t2 = new Transactions("2222", "1111", 2500.0);
			
			transRepo.save(t1);
			transRepo.save(t2);
			
		}
			
	}
	
	
	public class CustomResponse {
	    private String message;
	    private Object data;

	    public CustomResponse(String message, Object data) {
	        this.message = message;
	        this.data = data;
	    }

	    public String getMessage() {
	        return message;
	    }

	    public Object getData() {
	        return data;
	    }
	}
	
	
	public class transResponse {
		
		@Id private String id;
		public Accounts from;
		public Accounts to;
		public LocalDateTime createDate =LocalDateTime.now();
		double amount;
		
		public transResponse () {	
					
		}
		
		public transResponse (Transactions T, AccountsRepo accRepo) {
			
			
			this.from= accRepo.findByid(T.fromAcc).get(0);	
			this.to=accRepo.findByid(T.toAcc).get(0);
			this.amount = T.amount;
					
		}
		
	}
	
	
	public class AccSumClass {
		
		Accounts acc;					//bu kurtarır mı??
		List<transResponse> transOut;
		List<transResponse> transIn;
		double balance;
		
		public AccSumClass(Accounts acc, List<transResponse> transOut, List<transResponse> transIn, double balance) {
			this.acc=acc;
			this.transOut = transOut;
			this.transIn = transIn;
			this.balance = balance;
		}
		
		
		public AccSumClass() {


		}
		
		
	}

	
	
	@PostMapping("/account/save")
	public CustomResponse createAccount (@RequestBody Accounts newAcc) {
		
		Accounts myAcc = accRepo.save(newAcc);
		CustomResponse response = new CustomResponse("Success", myAcc);
		
		return response;
		
	}
	
	
	@PostMapping("/transaction/save")
	public CustomResponse createTransaction (@RequestBody Transactions newTrans) {
		
		try {
			Transactions myTrans = transRepo.save(newTrans);	//calisiyo	
		
			transResponse data = new transResponse(myTrans, accRepo);
			
		    CustomResponse response = new CustomResponse("Success", data);
			 
			return response;
		} 
		catch (Exception e) {
			
			CustomResponse response = new CustomResponse("ERROR account doesn’t exist", null);
			
			return response;
		}
		
	}
	
	
	@GetMapping("/account/{accountId}")
	public CustomResponse accountSum (@PathVariable String Id) {
		
		try {
			Accounts myAcc = accRepo.findByid(Id).get(0);
			
			List<Transactions> FromT = transRepo.findOut(Id);
			List<Transactions> ToT = transRepo.findIn(Id);
			
			List<transResponse> fromList = new ArrayList<>();	
			List<transResponse> toList = new ArrayList<>();	
			
			double balance=0.0;
			
			for (Transactions t : FromT) {
				
				transResponse myTR = new transResponse(t, accRepo);
				fromList.add(myTR);
				
				balance = balance - t.amount;
			}
			
			for (Transactions t : ToT) {
				
				toList.add(new transResponse(t, accRepo));
				
				balance = balance + t.amount;
			}
			
			AccSumClass mySum = new AccSumClass(myAcc, fromList, toList, balance); // transactionları transResponse'a çevir
			CustomResponse response = new CustomResponse("Success", mySum);
			
			return response;
	}	catch (Exception e) {
			
			CustomResponse response = new CustomResponse("ERROR: account doesn’t exist", null);
			
			return response;
		}
	}
	
	
	@GetMapping("/transaction/to/{accountId}")
	public CustomResponse transTo (@PathVariable String Id) {

		try {
			List<Transactions> myTs = transRepo.findIn(Id); //list of transactions			
	
			List<transResponse> myList = new ArrayList<>();		
					
			for (Transactions tr : myTs) {
				
				myList.add(new transResponse(tr, accRepo));
			}
				
			CustomResponse response = new CustomResponse("Success", myList);
			
			return response;
		}
		catch (Exception e) {
			
			CustomResponse response = new CustomResponse("ERROR: account doesn’t exist", null);
			
			return response;
		}
	}
	
	
	@GetMapping("/transaction/from/{accountId}")
	public CustomResponse transFrom (@PathVariable String Id) {
		
		
		try {
			List<Transactions> myTs = transRepo.findOut(Id); //list of transactions			
	
			List<transResponse> myList = new ArrayList<>();		
					
			for (Transactions tr : myTs) {
				
				myList.add(new transResponse(tr, accRepo));
			}
				
			CustomResponse response = new CustomResponse("Success", myList);
			
			return response;
			
		} catch (Exception e) {
			
			CustomResponse response = new CustomResponse("ERROR: account doesn’t exist", null);
			
			return response;
		}
	}
	
	
}
